## Problem Description

https://leetcode.com/problems/valid-triangle-number

```
Given an integer array nums, return the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.

Example 1:

Input: nums = [2,2,3,4]
Output: 3
Explanation: Valid combinations are: 
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3

Example 2:

Input: nums = [4,2,3,4]
Output: 4

Constraints:

1 <= nums.length <= 1000
0 <= nums[i] <= 1000
```

## Observations

The constraints are small, possibly applying brute-force.

Triangle inequality rule: For three sides ```a```, ```b```, and ```c```, the triangle is valid if:

```
a + b > c
a + c > b
b + c > a
```

If we sort the array, say in non-decreasing order:

Let ```c``` be the largest side. Then we only need to check whether ```a + b > c```, because the other two inequalities will automatically hold (```c ≥ a, b``` in sorted order).

A brute-force approach would try all triplets ```(a, b, c)``` in ```O(N^3)```. With ```N ≤ 1000```, this might still pass but is not efficient.

We can do better with sorting + two pointers in O(N^2).

**A better approach**:

Sort the array nums in non-decreasing order.

Iterate ```c``` from the last index ```(n-1)``` down to ```2```. This ensures that ```nums[c]``` is the largest side of the triangle.

For each ```c```, use two pointers:

```left = 0 (start of array)```

```right = c - 1 (just before c)```

While ```left < right```:

If ```nums[left] + nums[right] > nums[c]```, then all elements between left and ```right-1``` combined with ```nums[right]``` and ```nums[c]``` will form valid triangles.

So we can add ```(right - left)``` to the count and move right leftward.

Otherwise, if ```nums[left] + nums[right] <= nums[c]```, we need a larger sum, so move left rightward.

Continue until all ```c``` values are processed.

## Complexity

Sorting: ```O(N log N)```

Two-pointers scanning: For each ```c```, the left and right pointers traverse at most ```O(N)``` steps. Repeated for ```N``` values of ```c```.

```Total = O(N^2)```

## Tags

array, two pointers, math