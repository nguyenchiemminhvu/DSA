## Problem

https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

```
Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.

If target is not found in the array, return [-1, -1].

You must write an algorithm with O(log n) runtime complexity.

Example 1:

Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]

Example 2:

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]

Example 3:

Input: nums = [], target = 0
Output: [-1,-1]

Constraints:

0 <= nums.length <= 105
-109 <= nums[i] <= 109
nums is a non-decreasing array.
-109 <= target <= 109
```

## Observations

The input array is sorted in non-decreasing order.

We need to find the first and last positions of a given target value.

If the target is not found, return `[-1, -1]`.

A brute-force approach would scan the array linearly, but since the array is sorted, we can use binary search for efficiency.

## Solution

We use two standard library functions:

`std::lower_bound`: Finds the first position where the target could be inserted without breaking the order (i.e., the first occurrence of the target).

`std::upper_bound`: Finds the first position where a value greater than the target could be inserted (i.e., just after the last occurrence of the target).

**Steps**

Use `lower_bound` to find the first occurrence of the target.

If the target is not found, return `[-1, -1]`.

Use `upper_bound` to find the position just after the last occurrence.

The last occurrence is at `upper_bound - 1`.

Return the indices of the first and last occurrences.

Both `lower_bound` and `upper_bound` use binary search internally.
Time complexity is `O(logn)`, much faster than scanning the whole array.

## Tags

array, binary search