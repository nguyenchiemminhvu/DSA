## Problem

https://leetcode.com/problems/maximum-sum-of-two-non-overlapping-subarrays/description

````markdown
# Maximum Sum of Two Non-Overlapping Subarrays

## Problem

https://leetcode.com/problems/maximum-sum-of-two-non-overlapping-subarrays/description

Given an integer array `nums` and two integers `firstLen` and `secondLen`, return the **maximum sum** of elements in two non-overlapping subarrays with lengths `firstLen` and `secondLen`.

The subarray with length `firstLen` can occur before or after the subarray with length `secondLen`, but they **must not overlap**.

### Examples

**Example 1:**
- Input: `nums = [0,6,5,2,2,5,1,9,4]`, `firstLen = 1`, `secondLen = 2`
- Output: `20`
- Explanation: `[9]` (length 1) + `[6,5]` (length 2) = 9 + 11 = 20

**Example 2:**
- Input: `nums = [3,8,1,3,2,1,8,9,0]`, `firstLen = 3`, `secondLen = 2`
- Output: `29`
- Explanation: `[3,8,1]` (length 3) + `[8,9]` (length 2) = 12 + 17 = 29

**Example 3:**
- Input: `nums = [2,1,5,6,0,9,5,0,3,8]`, `firstLen = 4`, `secondLen = 3`
- Output: `31`
- Explanation: `[5,6,0,9]` (length 4) + `[0,3,8]` (length 3) = 20 + 11 = 31

### Constraints
- `1 <= firstLen, secondLen <= 1000`
- `2 <= firstLen + secondLen <= 1000`
- `firstLen + secondLen <= nums.length <= 1000`
- `0 <= nums[i] <= 1000`

---

## Observations

### 1. **Two Possible Orderings**
   - The subarray of length `firstLen` can appear **before** or **after** the subarray of length `secondLen`
   - Both orderings must be explored to guarantee the maximum sum
   - This symmetry suggests solving a helper function `F(n1, n2)` = max sum where the `n1`-subarray comes before the `n2`-subarray, then taking `max(F(n1, n2), F(n2, n1))`

### 2. **Subarray Sum Queries with Prefix Sums**
   - Summing any subarray `nums[i..i+k-1]` from scratch is O(k) — too slow if done repeatedly
   - A **prefix sum array** allows answering any subarray sum query in O(1):
     $$\text{sum}(i, i+k) = \text{prefix}[i+k] - \text{prefix}[i]$$
   - Precomputing `prefix_sum` of size `n+1` reduces the inner calculation to constant time

### 3. **Brute Force is Feasible Given Constraints**
   - `nums.length <= 1000`, so O(n²) is at most 10⁶ operations — well within limits
   - For each starting position `i` of the first subarray, iterate over all valid starting positions `j >= i + n1` for the second subarray
   - This ensures non-overlapping by construction: the second subarray always starts after the first ends

### 4. **Non-Overlap Guarantee via Index Constraint**
   - First subarray covers indices `[i, i + n1 - 1]`
   - Second subarray must start at `j >= i + n1` to avoid any overlap
   - The loop range for `j` is `[i + n1, n - n2]` (inclusive), which guarantees non-overlap

### 5. **All Elements Non-Negative**
   - Since `0 <= nums[i] <= 1000`, longer subarrays never "hurt" a sum
   - The maximum is guaranteed to exist and is always ≥ 0

---

## Solution

### Algorithm: Prefix Sum + Brute Force Enumeration

**Time Complexity**: O(n²) — two nested loops over valid subarray start positions  
**Space Complexity**: O(n) — for the prefix sum array

### Key Steps

1. **Build a prefix sum array** of size `n+1` where `prefix_sum[i+1] = prefix_sum[i] + nums[i]`
2. **Define helper `F(n1, n2)`**: fix the `n1`-subarray starting at index `i`, then scan all valid starting positions `j` for the `n2`-subarray to the right
3. **Call `max(F(n1, n2), F(n2, n1))`** to cover both orderings

### Code Walkthrough

```python
class Solution:
    def maxSumTwoNoOverlap(self, nums: List[int], n1: int, n2: int) -> int:
        n = len(nums)

        # Step 1: Build prefix sum array
        # prefix_sum[i] = sum of nums[0..i-1]
        prefix_sum = [0] * (n + 1)
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + nums[i]
        
        # Step 2: Helper — n1-subarray must come BEFORE n2-subarray
        def F(n1: int, n2: int) -> int:
            res = 0
            # i: start index of the first (n1-length) subarray
            for i in range(n - n1 + 1):
                s_from_i = prefix_sum[i + n1] - prefix_sum[i]   # sum of nums[i..i+n1-1]
                # j: start index of the second (n2-length) subarray, must be >= i+n1
                for j in range(i + n1, n - n2 + 1):
                    s_from_j = prefix_sum[j + n2] - prefix_sum[j]  # sum of nums[j..j+n2-1]
                    res = max(res, s_from_i + s_from_j)
            return res
        
        # Step 3: Try both orderings and return the maximum
        return max(F(n1, n2), F(n2, n1))
```

### Execution Flow Example

**Input**: `nums = [0,6,5,2,2,5,1,9,4]`, `n1 = 1`, `n2 = 2`

```
prefix_sum = [0, 0, 6, 11, 13, 15, 20, 21, 30, 34]

F(1, 2): fix n1=1 subarray at each index i, then find best n2=2 subarray to the right
  i=0, s=[0]:     best pair includes [6,5] at j=1 → 0+11=11
  i=6, s=[1]:     best pair includes [9,4] at j=7 → 1+13=14
  i=7, s=[9]:     j=8 only: [4] invalid (n2=2 needs 2 elements) → no valid j
  ...
  best from F(1,2) = 20  (i=7 → s=9, j=? — actually i=7 gives s=9, j=8 gives [4] — length issue)
  Correct: i=7 (s=[9]=9), j must be >=8 but n-n2+1=8, so j=8 is valid: sum=[4]=4 → 13
  The best is i=1 (s=[6]=6), j=2: [5,2]=7 → 13; or i=0 (s=[0]), j=1: [6,5]=11 → 11
  Actually: F(1,2) finds that when i=7 (s=9), no j with n2=2 fits to the right
  Best from F(1,2): i=1, j=3 → 6+7=13  ... max tracked across all pairs

F(2, 1): fix n2=2 subarray, then find best n1=1 subarray to the right
  i=1, s=[6,5]=11, j=3..7: best single element is nums[7]=9 → 11+9=20 ✓

Result: max(F(1,2), F(2,1)) = max(13, 20) = 20
```

### Why This Works

1. **Prefix sums eliminate redundant addition**: each subarray sum is computed in O(1) rather than O(k)
2. **`j >= i + n1` enforces non-overlap**: the second subarray always starts strictly after the first ends
3. **Trying both orderings via `F(n1,n2)` and `F(n2,n1)`** covers every valid non-overlapping pair of positions
4. **All values non-negative**: the global maximum is always the best combination we find

---

## Tags

- **Prefix Sum**: Fast subarray sum queries
- **Brute Force / Enumeration**: Iterate over all valid non-overlapping placement pairs
- **Sliding Window**: Variant — fixed-length window sum using prefix sums
- **Array**: Core data structure problem

````
