## Problem

https://leetcode.com/problems/search-in-rotated-sorted-array/description/

```
There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is possibly left rotated at an unknown index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be left rotated by 3 indices and become [4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

Example 3:

Input: nums = [1], target = 0
Output: -1

Constraints:

1 <= nums.length <= 5000
-104 <= nums[i] <= 104
All values of nums are unique.
nums is an ascending array that is possibly rotated.
-104 <= target <= 104
```

## Observations

The array is sorted but rotated at some unknown pivot. For example, `[4,5,6,7,0,1,2]` is a rotation of `[0,1,2,4,5,6,7]`.

There are no duplicate elements.

The rotation splits the array into two sorted subarrays.

Binary search can still be applied, but we need to determine which part is sorted at each step.

At any index, at least one side (`left` or `right`) of the array is sorted.

## Solution

1. Modified Binary Search:

- Start with two pointers, `left` and `right`, at the ends of the array.
- Find the middle index mid.
- If `nums[mid]` is the `target`, return `mid`.
- Determine which side is sorted:
  - If n`ums[left] <= nums[mid]`, the left side is sorted.
  - If `nums[mid] <= nums[right]`, the right side is sorted.
- Decide which side to search next:
  - If the left side is sorted and the target is within `nums[left]` and `nums[mid]`, search the left half.
  - If the right side is sorted and the target is within `nums[mid]` and `nums[right]`, search the right half.
  - Otherwise, search the other half.
- Repeat until the target is found or the search space is empty.

## Tags

array, sorting, binary search, recursion