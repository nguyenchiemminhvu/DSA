## Problem Description

https://leetcode.com/problems/rotate-array/description/

```
Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

Example 2:

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]

Constraints:

1 <= nums.length <= 105
-231 <= nums[i] <= 231 - 1
0 <= k <= 105

Follow up:

Try to come up with as many solutions as you can. There are at least three different ways to solve this problem.
Could you do it in-place with O(1) extra space?
```

## Observations

**Rotation means shifting elements:**

Rotating the array by `k` steps means each element moves `k` positions to the right. Elements that go past the end wrap around to the front.

**In-place requirement:**

We must rearrange the array without using extra arrays (space complexity `O(1)`).

**Modulo operation:**

If `k` is greater than the array length, rotating by `k` is the same as rotating by `k % n` (where `n` is the array length).

## Solutions

The optimal solution uses the reverse method:

**Reverse the first part:**

Reverse the elements before the `pivot` (the part that will move to the end).

**Reverse the second part:**

Reverse the elements after the `pivot` (the part that will move to the front).

**Reverse the whole array:**

This puts all elements in their correct rotated positions.

Suppose `nums = [1, 2, 3, 4, 5, 6, 7], k = 3`

```
k %= n:
k = 3 % 7 = 3

Find pivot:
pivot = n - k = 7 - 3 = 4

Reverse first part (0 to 3):
[1, 2, 3, 4] → [4, 3, 2, 1]

Array: [4, 3, 2, 1, 5, 6, 7]

Reverse second part (4 to 6):
[5, 6, 7] → [7, 6, 5]

Array: [4, 3, 2, 1, 7, 6, 5]

Reverse whole array (0 to 6):
[4, 3, 2, 1, 7, 6, 5] → [5, 6, 7, 1, 2, 3, 4]

Final result: [5, 6, 7, 1, 2, 3, 4]
```

## Tags

array, two pointers