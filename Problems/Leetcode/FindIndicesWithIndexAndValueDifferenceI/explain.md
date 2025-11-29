## Problem

https://leetcode.com/problems/find-indices-with-index-and-value-difference-i/description/

```
You are given a 0-indexed integer array nums having length n, an integer indexDifference, 
and an integer valueDifference.

Your task is to find two indices i and j, both in the range [0, n - 1], that satisfy the 
following conditions:

- abs(i - j) >= indexDifference, and
- abs(nums[i] - nums[j]) >= valueDifference

Return an integer array answer, where answer = [i, j] if there are two such indices, and 
answer = [-1, -1] otherwise. If there are multiple choices for the two indices, return any 
of them.

Note: i and j may be equal.

Example 1:
Input: nums = [5,1,4,1], indexDifference = 2, valueDifference = 4
Output: [0,3]
Explanation: i = 0 and j = 3 satisfy both conditions:
abs(0 - 3) = 3 >= 2 and abs(nums[0] - nums[3]) = abs(5 - 1) = 4 >= 4

Example 2:
Input: nums = [2,1], indexDifference = 0, valueDifference = 0
Output: [0,0]
Explanation: Any pair of indices works since both differences can be 0.

Example 3:
Input: nums = [1,2,3], indexDifference = 2, valueDifference = 4
Output: [-1,-1]
Explanation: No valid pair exists.

Constraints:
- 1 <= n == nums.length <= 100
- 0 <= nums[i] <= 50
- 0 <= indexDifference <= 100
- 0 <= valueDifference <= 50
```

## Observations

1. **Two conditions must be satisfied simultaneously:**
   - Index difference: `abs(i - j) >= indexDifference`
   - Value difference: `abs(nums[i] - nums[j]) >= valueDifference`

2. **Small constraints:** With `n <= 100`, a brute force $O(n^2)$ solution is acceptable.

3. **Optimization opportunity:** Since we need `abs(i - j) >= indexDifference`, for each index `i`, we only need to check indices `j` where `j >= i + indexDifference`. This reduces unnecessary comparisons.

4. **Early return:** We can return immediately upon finding the first valid pair, as the problem accepts any valid answer.

5. **Edge case:** When `indexDifference = 0` and `valueDifference = 0`, any pair works (including `[0, 0]`).

## Solution

**Algorithm:**
1. Iterate through each index `i` from 0 to n-1
2. For each `i`, iterate through indices `j` starting from `i + indexDifference` to n-1
   - By starting at `i + indexDifference`, we guarantee `j - i >= indexDifference`
   - This automatically satisfies the index difference condition
3. Check if the value difference condition is met: `abs(nums[i] - nums[j]) >= valueDifference`
4. If both conditions are satisfied, return `[i, j]` immediately
5. If no valid pair is found after checking all combinations, return `[-1, -1]`

**Why this works:**
- The inner loop starts at `j = i + indexDifference`, ensuring `j >= i + indexDifference`
- Since `j >= i`, we have `j - i >= indexDifference`, satisfying the first condition
- We explicitly check the value difference for the second condition
- The first valid pair found is returned (any valid answer is acceptable)

**Complexity Analysis:**
- **Time Complexity:** $O(n^2)$ - In the worst case, we check all pairs where the index difference is at least `indexDifference`
- **Space Complexity:** $O(1)$ - Only using a constant amount of extra space

**Alternative Approach (Optimal for larger inputs):**
For larger constraints, we could optimize to $O(n)$ by maintaining the minimum and maximum values seen so far as we iterate. For each position `j`, we check against the min/max from positions before `j - indexDifference`. However, given the constraint `n <= 100`, the brute force approach is simpler and sufficient.

# Tags
`Array` `Two Pointers` `Brute Force`

