## Problem

https://leetcode.com/problems/longest-even-odd-subarray-with-threshold/description/

You are given a 0-indexed integer array `nums` and an integer `threshold`.

Find the length of the longest subarray of `nums` starting at index `l` and ending at index `r` (0 <= l <= r < nums.length) that satisfies the following conditions:

1. `nums[l] % 2 == 0` (starts with an even number)
2. For all indices i in the range [l, r - 1], `nums[i] % 2 != nums[i + 1] % 2` (alternating even/odd pattern)
3. For all indices i in the range [l, r], `nums[i] <= threshold` (all elements within threshold)

Return an integer denoting the length of the longest such subarray.

**Example 1:**
```
Input: nums = [3,2,5,4], threshold = 5
Output: 3
Explanation: Subarray [2,5,4] starts at index 1, has alternating even/odd, and all ≤ 5
```

**Example 2:**
```
Input: nums = [1,2], threshold = 2
Output: 1
Explanation: Subarray [2] starts at index 1 (even), length 1
```

**Example 3:**
```
Input: nums = [2,3,4,5], threshold = 4
Output: 3
Explanation: Subarray [2,3,4] starts at index 0, alternating pattern, all ≤ 4
```

**Constraints:**
- 1 <= nums.length <= 100
- 1 <= nums[i] <= 100
- 1 <= threshold <= 100

## Observations

1. **Three Constraints to Satisfy:**
   - Must start with an even number
   - Must have alternating even/odd pattern
   - All elements must be ≤ threshold

2. **Key Insight - Split by Threshold:**
   - Elements > threshold act as natural boundaries
   - We can split the array into subarrays where all elements ≤ threshold
   - Only need to search within these valid subarrays

3. **Alternating Pattern:**
   - Even, Odd, Even, Odd, ... pattern
   - Can check using `num & 1` (bitwise AND) to determine parity
   - 0 means even, 1 means odd

4. **Search Strategy:**
   - Within each threshold-valid subarray, find all positions starting with even numbers
   - From each even starting position, extend as far as the alternating pattern holds
   - Track the maximum length found

5. **Edge Cases:**
   - Array with all odd numbers → result is 0 (no valid starting position)
   - Array with all numbers > threshold → result is 0
   - Single even element ≤ threshold → result is 1

## Solution

### Approach: Split and Search

The solution uses a two-phase approach:

**Phase 1: Split by Threshold**
- Create subarrays containing only elements ≤ threshold
- Elements > threshold cannot be part of any valid subarray

**Phase 2: Find Longest Alternating Subarray Starting with Even**
- For each threshold-valid subarray:
  - Iterate through all positions
  - If position has an even number, start a potential subarray
  - Extend while maintaining alternating even/odd pattern
  - Track maximum length

### Implementation Details

```python
def split_threshold(arr: List[int], threshold: int) -> List[List[int]]:
    arr.append(threshold + 1)  # Add sentinel to flush last subarray
    arrs = []
    cur_arr = []
    for val in arr:
        if val <= threshold:
            cur_arr.append(val)
        else:
            arrs.append(cur_arr)
            cur_arr = []
    arr.pop()  # Remove sentinel
    return arrs
```

**Main Algorithm:**
```python
res = 0
arrs = split_threshold(nums, threshold)

for arr in arrs:
    na = len(arr)
    for i in range(na):
        if arr[i] & 1:  # Skip odd numbers (can't start subarray)
            continue
        
        sign = 1  # Next expected parity (1 = odd, 0 = even)
        j = i + 1
        while j < na and (arr[j] & 1) == sign:
            j += 1
            sign = (sign + 1) % 2  # Alternate between 1 and 0
        res = max(res, j - i)

return res
```

### Complexity Analysis

**Time Complexity: O(n²)**
- Splitting by threshold: O(n)
- For each element in worst case: O(n) nested iterations
- Overall: O(n²) but in practice much better due to early termination

**Space Complexity: O(n)**
- Storage for split subarrays: O(n) in worst case
- When all elements ≤ threshold, we store a copy of the array

### Example Walkthrough

**Input:** `nums = [3,2,5,4]`, `threshold = 5`

1. **Split by threshold:**
   - All elements ≤ 5
   - Result: `[[3,2,5,4]]`

2. **Search in [3,2,5,4]:**
   - i=0: arr[0]=3 is odd → skip
   - i=1: arr[1]=2 is even → start
     - sign=1 (expect odd)
     - j=2: arr[2]=5, 5&1=1 ✓, sign→0
     - j=3: arr[3]=4, 4&1=0 ✓, sign→1
     - j=4: out of bounds
     - Length: 4-1 = 3
   - i=2: arr[2]=5 is odd → skip
   - i=3: arr[3]=4 is even → start
     - j=4: out of bounds
     - Length: 4-3 = 1

3. **Result:** max(3, 1) = 3

# Tags

`Array` `Sliding Window` `Two Pointers` `Bit Manipulation` `Greedy`

