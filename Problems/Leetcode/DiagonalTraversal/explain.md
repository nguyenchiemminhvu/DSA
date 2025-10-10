## Problem Description

https://leetcode.com/problems/diagonal-traverse/

```
Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.

Example 1:

Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,4,7,5,3,6,8,9]

Example 2:

Input: mat = [[1,2],[3,4]]
Output: [1,2,3,4]

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 104
1 <= m * n <= 104
-105 <= mat[i][j] <= 105
```

## Observations

The matrix is traversed diagonally, starting from the top-left corner.

Each diagonal starts at either the first row or the last column.

The direction of traversal alternates for each diagonal: one goes down-left, the next goes up-right (by reversing the order).

We need to collect elements from each diagonal and then combine them in the correct order.

## Solution

**Identify Diagonals:**

The total number of diagonals is 

`m + n − 1`

where

`m` is the number of rows.

`n` is the number of columns.

For each diagonal, we figure out where it starts (either at the top row or the leftmost column).

**Collect Diagonal Elements:**

For each diagonal, we move from the starting point down and to the right, collecting elements until we go out of bounds.

**Alternate Direction:**

To get the zigzag pattern, we reverse every other diagonal before adding its elements to the result.

**Build the Result:**

After collecting all diagonals, we combine them into a single list, alternating the direction as needed.

## Tags

array