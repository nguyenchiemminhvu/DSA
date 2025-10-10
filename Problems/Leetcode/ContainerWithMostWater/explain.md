## Problem Description

https://leetcode.com/problems/container-with-most-water/description/

```
You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.

Example 1:

Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.

Example 2:

Input: height = [1,1]
Output: 1

Constraints:

n == height.length
2 <= n <= 105
0 <= height[i] <= 104
```

## Observations

The problem asks you to find the maximum area of water that can be contained between two lines in an array, where each element represents the height of a line.

The area between two lines is determined by the shorter line and the distance between them.

If you fix one line and try all possible pairs, it will be slow (brute force).
Instead, you can use two pointers: one at the start (left), one at the end (right).

At each step, the area is calculated using the lines at left and right.
To potentially find a bigger area, you move the pointer pointing to the shorter line inward, hoping to find a taller line.

## Solution

- Start with two pointers:
  - left at the beginning and right at the end of the array.
- Calculate the area between the lines at left and right:
  - ```Area = min(height[left], height[right]) × (right - left)```
  - Use the shorter line because water will spill over the shorter one.
- Update the maximum area found so far.
- Move the pointer pointing to the shorter line inward:
  - If height[left] is less than or equal to height[right], move left rightward.
  - Otherwise, move right leftward.
- Repeat until the pointers meet.
- Return the maximum area found.

This approach is efficient because it checks all possible pairs in a smart way, always trying to find a taller line that could increase the area, and only moving the pointer that could help.

## Tags

array, two pointers