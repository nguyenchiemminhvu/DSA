## Problem Description

https://leetcode.com/problems/squares-of-a-sorted-array/

```
Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.

Example 1:

Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Explanation: After squaring, the array becomes [16,1,0,9,100].
After sorting, it becomes [0,1,9,16,100].

Example 2:

Input: nums = [-7,-3,2,3,11]
Output: [4,9,9,49,121]

Constraints:

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums is sorted in non-decreasing order.

Follow up: Squaring each element and sorting the new array is very trivial, could you find an O(n) solution using a different approach?
```

## Observations

The constraints are small.

Array is sorted already.

Array could contain negative numbers, this impacts to the sorted order after making squares.

Bigger abs(value) would make bigger square value.

**A simple approach:**

Make all elements square value, then sort the array again. => ```O(N * log(N))```

**O(N) approach:**

Using two pointer technique, build a new sorted array like how merge sort work.

Move from left to right (0 -> n - 1), and right to left (n - 1 -> 0):

Which side have greater abs value, make square and append to the result array. This will produce a new sorted array in descreasing order. We finally need one more reverse step.

All this operations take N times.

## Tags

array, sorting