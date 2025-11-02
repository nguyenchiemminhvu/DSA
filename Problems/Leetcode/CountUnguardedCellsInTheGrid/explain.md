## Problem

https://leetcode.com/problems/count-unguarded-cells-in-the-grid/

```
You are given two integers m and n representing a 0-indexed m x n grid. You are also given two 2D integer arrays guards and walls where guards[i] = [rowi, coli] and walls[j] = [rowj, colj] represent the positions of the ith guard and jth wall respectively.

A guard can see every cell in the four cardinal directions (north, east, south, or west) starting from their position unless obstructed by a wall or another guard. A cell is guarded if there is at least one guard that can see it.

Return the number of unoccupied cells that are not guarded.

Example 1:

Input: m = 4, n = 6, guards = [[0,0],[1,1],[2,3]], walls = [[0,1],[2,2],[1,4]]
Output: 7
Explanation: The guarded and unguarded cells are shown in red and green respectively in the above diagram.
There are a total of 7 unguarded cells, so we return 7.

Example 2:

Input: m = 3, n = 3, guards = [[1,1]], walls = [[0,1],[1,0],[2,1],[1,2]]
Output: 4
Explanation: The unguarded cells are shown in green in the above diagram.
There are a total of 4 unguarded cells, so we return 4.

Constraints:

1 <= m, n <= 105
2 <= m * n <= 105
1 <= guards.length, walls.length <= 5 * 104
2 <= guards.length + walls.length <= m * n
guards[i].length == walls[j].length == 2
0 <= rowi, rowj < m
0 <= coli, colj < n
All the positions in guards and walls are unique.
```

## Observations

1. **Grid Representation**: We need to track different cell types in the grid:
   - `-1`: Unguarded cells (initially all cells)
   - `0`: Guarded cells (cells that guards can see)
   - `1`: Wall cells (block guard vision)
   - `2`: Guard cells (source of vision)

2. **Guard Vision Pattern**: Guards can see in all 4 cardinal directions (north, south, east, west) until they hit a wall or another guard.

3. **Line-of-Sight Algorithm**: We can process the grid by scanning each row and column in both directions:
   - For each row: scan left-to-right and right-to-left
   - For each column: scan top-to-bottom and bottom-to-top

4. **State Machine Approach**: For each scan direction, we maintain a `can_see` boolean flag:
   - When we encounter a guard (`2`), set `can_see = True`
   - When we encounter a wall (`1`), set `can_see = False` (vision blocked)
   - When we encounter an empty cell (`-1`) and `can_see = True`, mark it as guarded (`0`)

## Solution

1. **Initialization**: Create a grid where all cells are initially marked as `-1` (unguarded).

2. **Setup**: Place walls (`1`) and guards (`2`) in their respective positions.

3. **Horizontal Processing**: For each row, scan left-to-right and right-to-left to mark cells guarded by horizontal line-of-sight.

4. **Vertical Processing**: For each column, scan top-to-bottom and bottom-to-top to mark cells guarded by vertical line-of-sight.

5. **Counting**: Count all cells that remain `-1` (unguarded).

**Time Complexity**: O(m × n) - We scan each cell at most 4 times (once per direction).

**Space Complexity**: O(m × n) - For the grid storage.

**Key Insight**: The bidirectional scanning approach ensures we capture all guard vision lines efficiently without complex ray-casting algorithms.

## Tags

- Grid
- Simulation
- Array Processing
- Line-of-Sight Algorithm

