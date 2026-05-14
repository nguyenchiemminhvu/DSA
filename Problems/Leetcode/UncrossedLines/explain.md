## Problem

https://leetcode.com/problems/uncrossed-lines/description

You are given two integer arrays `nums1` and `nums2`. We write the integers of `nums1` and `nums2` (in the order they are given) on two separate horizontal lines.

We may draw connecting lines: a straight line connecting two numbers `nums1[i]` and `nums2[j]` such that:
- `nums1[i] == nums2[j]`, and
- the line we draw does not intersect any other connecting (non-horizontal) line.

Note that a connecting line cannot intersect even at the endpoints (i.e., each number can only belong to one connecting line).

**Return the maximum number of connecting lines we can draw in this way.**

### Examples

**Example 1:**
```
Input: nums1 = [1,4,2], nums2 = [1,2,4]
Output: 2
Explanation: We can draw 2 uncrossed lines as in the diagram.
We cannot draw 3 uncrossed lines, because the line from nums1[1] = 4 to nums2[2] = 4 
will intersect the line from nums1[2]=2 to nums2[1]=2.
```

**Example 2:**
```
Input: nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
Output: 3
```

**Example 3:**
```
Input: nums1 = [1,3,7,1,7,5], nums2 = [1,9,2,5,1]
Output: 2
```

### Constraints

- $1 \leq \text{nums1.length}, \text{nums2.length} \leq 500$
- $1 \leq \text{nums1[i]}, \text{nums2[j]} \leq 2000$

## Observations

1. **Key Insight: Non-intersection constraint is the key**
   - Two lines connecting `(i1, j1)` and `(i2, j2)` don't intersect if and only if:
     - `i1 < i2` and `j1 < j2`, OR `i1 > i2` and `j1 > j2`
     - In other words, the relative order must be preserved in both arrays

2. **This is equivalent to Longest Common Subsequence (LCS)**
   - We need to find the longest subsequence of elements that appear in both arrays in the same relative order
   - If we match elements greedily while preserving order in both arrays, we won't create intersections
   - Example: `nums1 = [1,4,2]`, `nums2 = [1,2,4]`
     - Common subsequences: `[1]` (length 1), `[4]` (length 1), `[2]` (length 1), `[1,4]` (invalid - not in order in nums2), `[1,2]` (length 2)
     - LCS is `[1,2]` with length 2

3. **Dynamic Programming approach**
   - State: `dp[i1][i2]` = maximum uncrossed lines using first `i1` elements of `nums1` and first `i2` elements of `nums2`
   - Transition:
     - If `nums1[i1] == nums2[i2]`: we can match these elements, so `dp[i1][i2] = 1 + dp[i1+1][i2+1]`
     - Otherwise: we skip one element from either array, so `dp[i1][i2] = max(dp[i1+1][i2], dp[i1][i2+1])`

4. **Why non-intersection is guaranteed**
   - By processing elements in order and only matching equal elements, we ensure that earlier matches don't interfere with later matches
   - If we match at position `i1` in `nums1` and `j2` in `nums2`, all subsequent matches will have indices > `i1` and > `j2`

## Solution

### Approach: Dynamic Programming (Bottom-Up)

The solution uses a 2D DP table where `dp[i1][i2]` represents the maximum number of uncrossed lines we can draw using elements from index `i1` onwards in `nums1` and index `i2` onwards in `nums2`.

**Algorithm:**
1. Create a DP table of size `(n1+1) × (n2+1)` initialized to 0
2. Fill the table from bottom-right to top-left (backward iteration)
3. For each position `(i1, i2)`:
   - If `nums1[i1] == nums2[i2]`: add 1 to the best solution from `(i1+1, i2+1)`
   - Otherwise: take the maximum of solutions from `(i1+1, i2)` or `(i1, i2+1)`
4. Return `dp[0][0]` which contains the answer for the entire arrays

**Time Complexity:** $O(n_1 \times n_2)$ where $n_1 = \text{len(nums1)}$ and $n_2 = \text{len(nums2)}$

**Space Complexity:** $O(n_1 \times n_2)$ for the DP table

**Why it works:**
- Each cell decision is made independently based on whether elements match
- The bottom-up approach ensures all subproblems are solved before being used
- The non-crossing property is automatically maintained because we only match elements with equal values while preserving order

### Alternative: Top-Down with Memoization

The commented-out code shows a top-down recursive approach with memoization:
```python
mem = {}
def F(i1: int, i2: int) -> int:
    if i1 >= n1 or i2 >= n2:
        return 0
    if (i1, i2) in mem:
        return mem[(i1, i2)]
    res = 0
    if nums1[i1] == nums2[i2]:
        res = max(res, 1 + F(i1 + 1, i2 + 1))
    else:
        res = max(res, max(F(i1 + 1, i2), F(i1, i2 + 1)))
    mem[(i1, i2)] = res
    return res
return F(0, 0)
```

Both approaches have identical time and space complexity, but the bottom-up DP is generally preferred for avoiding recursion overhead.

# Tags

#dp #greedy #lcs #subsequence #two-pointers

