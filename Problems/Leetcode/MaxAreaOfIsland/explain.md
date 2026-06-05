## Problem

https://leetcode.com/problems/max-area-of-island/description/

Given an `m x n` binary matrix `grid`, an **island** is a group of `1`s (land) connected **4-directionally** (horizontal or vertical). All four edges of the grid are surrounded by water.

The **area** of an island is the number of cells with value `1` in that island.

Return the **maximum area** of an island in `grid`. If there is no island, return `0`.

---

## Observations

- Each cell is either land (`1`) or water (`0`).
- Islands are formed by **4-directional connectivity** only — diagonal neighbors do NOT count.
- To avoid counting the same cell twice, we can **mark visited land cells as `0`** (sink the island) as we traverse them.
- The grid dimensions are small (`m, n ≤ 50`), so an O(m × n) DFS/BFS solution is well within limits.
- Every unvisited `1` is the starting point of a new island. We compute its area via DFS/BFS and track the maximum seen so far.

---

## Solution Explanation

### Approach: DFS with In-Place Marking

```python
class Solution:
    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        def dfs(r, c):
            if r < 0 or r >= m or c < 0 or c >= n:
                return 0
            if grid[r][c] == 0:
                return 0
            
            grid[r][c] = 0  # Mark as visited by sinking the cell
            s = 1            # Count this cell
            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                s += dfs(nr, nc)
            return s
        
        res = 0
        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1:
                    res = max(res, dfs(r, c))
        return res
```

### Step-by-step

1. **Iterate** over every cell `(r, c)` in the grid.
2. When a land cell (`grid[r][c] == 1`) is found, launch a **DFS** from it.
3. Inside `dfs(r, c)`:
   - **Base cases:** return `0` if out of bounds or the cell is water/already visited.
   - **Sink the cell:** set `grid[r][c] = 0` to prevent revisiting (acts as an implicit `visited` set).
   - **Recurse** in all 4 directions, accumulating the total area.
   - Return the **total area** of the connected component.
4. Update `res` with the maximum area returned by each DFS call.
5. Return `res` after scanning all cells.

### Complexity

| | |
|---|---|
| **Time** | O(m × n) — each cell is visited at most once |
| **Space** | O(m × n) — recursion stack depth in the worst case (entire grid is one island) |

