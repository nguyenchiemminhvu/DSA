## Problem

https://leetcode.com/problems/maximum-length-of-repeated-subarray/description

# Maximum Length of Repeated Subarray

## Problem

**LeetCode Link:** https://leetcode.com/problems/maximum-length-of-repeated-subarray/description

Given two integer arrays `nums1` and `nums2`, return the **maximum length of a subarray that appears in both arrays**.

### Examples

**Example 1:**
```
Input: nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7]
Output: 3
Explanation: The repeated subarray with maximum length is [3,2,1].
```

**Example 2:**
```
Input: nums1 = [0,0,0,0,0], nums2 = [0,0,0,0,0]
Output: 5
Explanation: The repeated subarray with maximum length is [0,0,0,0,0].
```

### Constraints

- 1 <= nums1.length, nums2.length <= 1000
- 0 <= nums1[i], nums2[i] <= 100

---

## Observations

1. **Subarray Definition:** We're looking for a **contiguous sequence** of elements that appears in both arrays with the same order and values.

2. **Brute Force Insight:** For each position in `nums1`, we could try to match it with each position in `nums2` and see how long a matching subarray we can build.

3. **Overlapping Subproblems:** When we're trying to match elements at position `i` in `nums1` and position `j` in `nums2`, the result depends on whether we've already matched elements before (at positions `i-1` and `j-1`).

4. **Recurrence Relation:** 
   - If `nums1[i] == nums2[j]`, then `dp[i][j] = 1 + dp[i-1][j-1]` (extend the previous match)
   - If `nums1[i] != nums2[j]`, then `dp[i][j] = 0` (no match at this position)

5. **State Definition:** `dp[i][j]` represents the **length of the longest common subarray ending at index `i` in `nums1` and index `j` in `nums2`**.

6. **Final Answer:** The maximum value in the entire `dp` table is our answer.

---

## Solution Approaches

### Approach 1: Top-Down Dynamic Programming (Memoization)
*(Commented out in the provided solution)*

**Idea:** Use recursion with memoization to compute the longest match starting backwards from the end indices.

```python
mem = {}
def F(i1: int, i2: int):
    if i1 < 0 or i2 < 0:
        return 0
    if (i1, i2) in mem:
        return mem[(i1, i2)]
    res = 0
    if nums1[i1] == nums2[i2]:
        res = max(res, 1 + F(i1 - 1, i2 - 1))
    else:
        res = 0
    mem[(i1, i2)] = res
    return res

res = 0
for i in range(n1):
    for j in range(n2):
        res = max(res, F(i, j))
return res
```

**Time Complexity:** O(n1 × n2) - Each subproblem is computed once  
**Space Complexity:** O(n1 × n2) - Memoization table + recursion stack

### Approach 2: Bottom-Up Dynamic Programming (Tabulation)
*(Provided solution)*

**Idea:** Build a 2D DP table iteratively where `dp[i][j]` represents the length of the longest common subarray ending at `nums1[i]` and `nums2[j]`.

**Algorithm:**
1. Create a 2D table `dp` of size `n1 × n2` initialized to 0
2. For each position `(i, j)`:
   - If `nums1[i] == nums2[j]`: extend the previous match → `dp[i][j] = 1 + dp[i-1][j-1]`
   - Otherwise: reset → `dp[i][j] = 0`
3. Return the maximum value in the table

**Time Complexity:** O(n1 × n2) - We iterate through all cells once  
**Space Complexity:** O(n1 × n2) - DP table storage

**Advantages:**
- Avoids recursion overhead
- Straightforward iterative approach
- Easier to understand and trace through

### Approach 3: Space-Optimized DP

We can optimize space by using only two rows since `dp[i][j]` only depends on `dp[i-1][j-1]`:

```python
prev = [0] * n2
curr = [0] * n2
max_len = 0

for i in range(n1):
    for j in range(n2):
        if nums1[i] == nums2[j]:
            curr[j] = 1 + prev[j-1]
            max_len = max(max_len, curr[j])
        else:
            curr[j] = 0
    prev, curr = curr, [0] * n2

return max_len
```

**Time Complexity:** O(n1 × n2)  
**Space Complexity:** O(n2) - Only store two rows

---

## Detailed Explanation of the Provided Solution

```python
dp = [[0] * n2 for _ in range(n1)]
for i in range(n1):
    for j in range(n2):
        if nums1[i] == nums2[j]:
            dp[i][j] = max(dp[i][j], 1 + (dp[i - 1][j - 1] if i - 1 >= 0 and j - 1 >= 0 else 0))
        else:
            dp[i][j] = 0
return max(max(row) for row in dp)
```

**Step-by-step walkthrough with Example 1:**

`nums1 = [1,2,3,2,1]`, `nums2 = [3,2,1,4,7]`

**DP Table Evolution:**

```
        3  2  1  4  7
    1  [0  0  0  0  0]
    2  [0  1  0  0  0]
    3  [1  0  1  0  0]
    2  [0  2  0  0  0]
    1  [0  0  3  0  0]
```

**Trace:**
- `(0,0)`: `nums1[0]=1 != nums2[0]=3` → `dp[0][0] = 0`
- `(1,1)`: `nums1[1]=2 == nums2[1]=2` → `dp[1][1] = 1 + dp[0][0] = 1`
- `(2,0)`: `nums1[2]=3 == nums2[0]=3` → `dp[2][0] = 1 + 0 = 1`
- `(2,2)`: `nums1[2]=3 == nums2[2]=1` ✗ → `dp[2][2] = 0`
- `(3,1)`: `nums1[3]=2 == nums2[1]=2` → `dp[3][1] = 1 + dp[2][0] = 2`
- `(4,2)`: `nums1[4]=1 == nums2[2]=1` → `dp[4][2] = 1 + dp[3][1] = 3` ✓

Maximum value = **3**

---

## Key Insights

1. **This is a classic DP problem** - The structure of overlapping subproblems makes it ideal for dynamic programming
2. **State representation matters** - `dp[i][j]` must represent "length ending at position (i,j)" not just "any match at (i,j)"
3. **Boundary conditions are crucial** - We need to handle the case when `i-1 < 0` or `j-1 < 0`
4. **DP table itself is the answer** - Unlike some problems, we need to check ALL cells, not just the last one

---

## Tags

- **Algorithm:** Dynamic Programming
- **Pattern:** 2D DP Tabulation
- **Difficulty:** Medium
- **Category:** Array, Dynamic Programming
- **Related Problems:** Longest Common Subsequence, Edit Distance

## Observations

## Solution

# Tags

