## Problem

https://leetcode.com/problems/increasing-triplet-subsequence/

```
Given an integer array nums, return true if there exists a triple of indices (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k]. If no such indices exists, return false.

Example 1:

Input: nums = [1,2,3,4,5]
Output: true
Explanation: Any triplet where i < j < k is valid.

Example 2:

Input: nums = [5,4,3,2,1]
Output: false
Explanation: No triplet exists.

Example 3:

Input: nums = [2,1,5,0,4,6]
Output: true
Explanation: One of the valid triplet is (3, 4, 5), because nums[3] == 0 < nums[4] == 4 < nums[5] == 6.

Constraints:

1 <= nums.length <= 5 * 105
-231 <= nums[i] <= 231 - 1

Follow up: Could you implement a solution that runs in O(n) time complexity and O(1) space complexity?
```

## Observations

1. The problem requires finding three indices `i`, `j`, and `k` such that `i < j < k` and `nums[i] < nums[j] < nums[k]`.
2. The constraints suggest that the solution must be efficient, ideally O(n) time complexity and O(1) space complexity.
3. A brute-force approach would involve checking all possible triplets, which is computationally expensive (O(n^3)).
4. The problem can be solved using a greedy approach by maintaining two variables to track the smallest and second smallest values encountered so far.
5. If a value greater than the second smallest is found, it confirms the existence of an increasing triplet.

## Solution

1. Initialize two variables `val1` and `val2` to a very large value (infinity).
2. Iterate through the array:
   - If the current value is less than or equal to `val1`, update `val1`.
   - Otherwise, if the current value is less than or equal to `val2`, update `val2`.
   - If the current value is greater than both `val1` and `val2`, return `True` (an increasing triplet is found).
3. If the loop completes without finding a triplet, return `False`.

### Complexity:
- **Time Complexity:** O(n), as the array is traversed once.
- **Space Complexity:** O(1), as only two variables are used.