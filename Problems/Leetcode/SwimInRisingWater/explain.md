## Problem

https://leetcode.com/problems/swim-in-rising-water/

```
You are given an n x n integer matrix grid where each value grid[i][j] represents the elevation at that point (i, j).

It starts raining, and water gradually rises over time. At time t, the water level is t, meaning any cell with elevation less than equal to t is submerged or reachable.

You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distances in zero time. Of course, you must stay within the boundaries of the grid during your swim.

Return the minimum time until you can reach the bottom right square (n - 1, n - 1) if you start at the top left square (0, 0).

Example 1:

Input: grid = [[0,2],[1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.

Example 2:


Input: grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
Output: 16
Explanation: The final route is shown.
We need to wait until time 16 so that (0, 0) and (4, 4) are connected.

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 50
0 <= grid[i][j] < n2
Each value grid[i][j] is unique.
```

## Observations

The `grid` represents a map where each cell contains an integer indicating the land height at that position.

Start at the top-left cell `(0, 0)` and must reach the bottom-right cell `(m-1, n-1)`.

Can only move to adjacent cells (`up`, `down`, `left`, `right`).

You can only enter a cell if the current time is at least equal to elevation of that land.

The goal is to minimize the time required to reach the bottom-right cell, which is equivalent to minimizing the maximum water level encountered along the path.

## Solution

The problem is solved using a modified `Dijkstra's algorithm`:

Each cell is treated as a node, and the "cost" to enter a cell is the maximum land evelation encountered so far.

A `min-heap` (priority queue) is used to always expand the path with the lowest current maximum land elevation.

For each cell, we keep track of the minimum water level required to reach it (`min_heights`).

We update neighboring cells if we find a path to them with a lower maximum water level.

The algorithm terminates when the bottom-right cell is reached, and the answer is the minimum water level required to reach it.

## Tags

array, graph