## Problem Description

https://leetcode.com/problems/minimum-size-subarray-sum/

```
Given an array of positive integers nums and a positive integer target, return the minimal length of a subarray whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.

Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.

Example 2:

Input: target = 4, nums = [1,4,4]
Output: 1

Example 3:

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0

Constraints:

1 <= target <= 109
1 <= nums.length <= 105
1 <= nums[i] <= 104

Follow up: If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log(n)).
```

## Observations

All numbers in `nums` are positive, so increasing the window size always increases the `sum`.

We need the shortest subarray whose `sum` is at least target.

A brute-force approach (checking all subarrays) is inefficient for large arrays.

## Solution

### Sliding Window Technique

Use `two pointers` (`left` and `right`) to represent the current window.

Expand the window by moving right and adding `nums[right]` to the current `sum`.

When the `sum` is at least `target`, try to shrink the window from the `left` to find the minimal length.

Update the minimal length whenever a valid window is found.

## Tags

array, two pointers