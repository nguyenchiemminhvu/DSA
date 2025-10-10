## Problem

https://leetcode.com/problems/01-matrix/description/

```
Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.

The distance between two cells sharing a common edge is 1.

Example 1:

Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
Output: [[0,0,0],[0,1,0],[0,0,0]]

Example 2:

Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
Output: [[0,0,0],[0,1,0],[1,2,1]]

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 104
1 <= m * n <= 104
mat[i][j] is either 0 or 1.
There is at least one 0 in mat.
```

## Observations

1. **Problem Nature**: This is a shortest path problem where we need to find the minimum distance from each cell to the nearest 0. This suggests using BFS (Breadth-First Search) since BFS guarantees the shortest path in unweighted graphs.

2. **Multi-source BFS**: Instead of running BFS from each cell (which would be `O(m²n²)`), we can use multi-source BFS. We start BFS simultaneously from all cells containing `0`, treating them as multiple sources.

3. **Distance Calculation**: The distance between adjacent cells (sharing an edge) is 1. This makes it perfect for BFS where each level represents one unit of distance.

4. **Matrix as Graph**: We can treat the matrix as an undirected graph where each cell is a node, and adjacent cells (up, down, left, right) are connected by edges.

5. **Optimization**: By starting from all `0s` simultaneously and expanding outward level by level, each cell will be reached by the shortest possible path first.

## Solution

The solution uses **Multi-source BFS** approach:

**Key Components:**

1. **Initialization**:
   - Create a `dp` matrix where cells with `0` remain `0`, and cells with `1` are set to infinity (`INF`)
   - Initialize a queue with all positions containing `0` as starting points
   - Use `steps` counter to track the current distance level

2. **BFS Process**:
   - Process all cells at the current distance level before moving to the next level
   - For each cell, check all `4` adjacent neighbors (`up`, `down`, `left`, `right`)
   - If a neighbor is within bounds, is not 0, and hasn't been reached by a shorter path, update its distance

3. **Level-by-level Expansion**:
   - `cur_len = len(Q)` ensures we process exactly one level at a time
   - After processing all cells at current level, increment `steps` for the next level
   - This guarantees that when we first reach a cell, it's via the shortest path

**Algorithm Flow:**
```
Level 0: All 0s are at distance 0
Level 1: All 1s adjacent to 0s are at distance 1  
Level 2: All 1s adjacent to level 1 cells are at distance 2
...and so on
```

**Time Complexity**: `O(m × n)` - each cell is visited at most once
**Space Complexity**: `O(m × n)` - for the dp matrix and queue storage

**Why it works**: BFS guarantees that when we first visit a cell, we've found the shortest path to it. The multi-source approach ensures we explore from all `0s` simultaneously, so distances are computed optimally.

## Tags

array, graph, bfs