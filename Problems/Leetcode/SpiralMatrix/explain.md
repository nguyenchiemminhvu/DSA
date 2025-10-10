## Problem Description

https://leetcode.com/problems/spiral-matrix/

```
Given an m x n matrix, return all elements of the matrix in spiral order.

Example 1:

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:

Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 10
-100 <= matrix[i][j] <= 100
```

## Observations

The spiral order means visiting the matrix in a clockwise pattern, starting from the ```top-left``` corner and moving ```right```, then ```down```, then ```left```, then ```up```, and repeating this process for the inner layers.

Each time you complete a loop around the ```matrix```, you move inward to the next layer.

We need to keep track of the boundaries (```top```, ```bottom```, ```left```, ```right```) to avoid revisiting elements.

The process continues until all elements are visited.

The ```matrix``` can be rectangular, not just square, so the number of ```rows``` and ```columns``` may differ.

We must ensure you do not go out of bounds or visit the same element twice.

## Solutions

### Approach 1: Boundary Tracking with Four Loops

Use four separate loops to traverse the matrix in the four directions:

Move right across the top row.

Move down the rightmost column.

Move left across the bottom row.

Move up the leftmost column.

After each direction, update the boundaries (```top```, ```bottom```, ```left```, ```right```) to move inward.

Repeat until all elements are visited.

### Approach 2: Generalized Directional Traversal (Your Solution)

Use direction arrays to represent movement: ```right```, ```down```, ```left```, ```up```.

Keep track of the current position and direction.

Use a visited ```matrix``` to mark which elements have been visited.

At each step, try to move in the current direction. If you hit a boundary or a visited cell, change direction.

Continue until all elements are added to the result.

## Tags

array