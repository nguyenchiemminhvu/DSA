## Problem

https://leetcode.com/problems/find-peak-element/

```
A peak element is an element that is strictly greater than its neighbors.

Given a 0-indexed integer array nums, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks.

You may imagine that nums[-1] = nums[n] = -∞. In other words, an element is always considered to be strictly greater than a neighbor that is outside the array.

You must write an algorithm that runs in O(log n) time.

Example 1:

Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.

Example 2:

Input: nums = [1,2,1,3,5,6,4]
Output: 5
Explanation: Your function can return either index number 1 where the peak element is 2, or index number 5 where the peak element is 6.

Constraints:

1 <= nums.length <= 1000
-231 <= nums[i] <= 231 - 1
nums[i] != nums[i + 1] for all valid i.
```

## Observations

A "peak element" in an array is an element that is strictly greater than its neighbors.

The array may contain multiple peaks; the task is to return the index of any one peak.

For edge cases:
- If the array has only one element, it is trivially a peak.
- The first and last elements can be peaks if they are greater than their only neighbor.

The problem can be solved efficiently using binary search, not just linear scan.

## Solution

- First, check the edge cases:
  - If the array has one element, return index `0`.
  - If the first element is greater than the second, return index `0`.
  - If the last element is greater than the second last, return the last index.
- For the rest of the array, use a recursive binary search:
  - Calculate the middle index.
  - If the middle element is greater than both neighbors, it is a `peak`; return its index.
  - Otherwise, recursively search the `left` and `right` halves.

This approach ensures `O(logn)` time complexity, making it efficient for large arrays.

## Tags

array, binary search