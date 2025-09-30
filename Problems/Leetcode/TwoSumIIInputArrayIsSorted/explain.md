## Problem Description

https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/

```
Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.

Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.

The tests are generated such that there is exactly one solution. You may not use the same element twice.

Your solution must use only constant extra space.

Example 1:

Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].

Example 2:

Input: numbers = [2,3,4], target = 6
Output: [1,3]
Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. We return [1, 3].

Example 3:

Input: numbers = [-1,0], target = -1
Output: [1,2]
Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. We return [1, 2].

Constraints:

2 <= numbers.length <= 3 * 104
-1000 <= numbers[i] <= 1000
numbers is sorted in non-decreasing order.
-1000 <= target <= 1000
The tests are generated such that there is exactly one solution.
```

## Observations

The input array is already sorted in ascending order.

We need to find two numbers whose sum equals the target.

The problem asks for `1-based` indices (not `0-based`).

## Solution

**Two Pointers Approach:**

Start with two pointers: one at the beginning (`left`) and one at the end (`right`) of the array.

Calculate the `sum` of the numbers at these pointers.

If the `sum` equals the `target`, return their indices (add 1 to each for 1-based indexing).

If the `sum` is less than the `target`, move the `left` pointer to the `right` (increase it) to get a larger `sum`.

If the `sum` is greater than the `target`, move the `right` pointer to the `left` (decrease it) to get a smaller `sum`.

Repeat until you find the answer.

**Example**

Suppose `nums = [2, 7, 11, 15]` and `target = 9`:

Init:

`left = 0 (nums[0] = 2), right = 3 (nums[3] = 15)`

Processing:

`2 + 15 = 17` (too big, move right left)

`2 + 11 = 13` (still too big, move right left)

`2 + 7 = 9` (found! return `[1, 2]`)

## Tags

array, two pointers