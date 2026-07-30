````markdown
## Problem

https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/description/

You are given a **0-indexed 2D matrix** `grid` of size `m x n`, where `(r, c)` represents:

- A **land cell** if `grid[r][c] = 0`, or
- A **water cell** containing `grid[r][c]` fish, if `grid[r][c] > 0`.

A fisher can start at **any water cell** and can repeatedly:

- **Catch all fish** at the current cell, or
- **Move** to any adjacent (4-directional) water cell.

Return the **maximum number of fish** the fisher can catch if he chooses his starting cell optimally, or `0` if no water cell exists.

**Example 1:**

```
Input:  grid = [[0,2,1,0],[4,0,0,3],[1,0,0,4],[0,3,2,0]]
Output: 7
```

The fisher starts at `(1,3)` → collects 3 fish, moves to `(2,3)` → collects 4 fish. Total = **7**.

**Example 2:**

```
Input:  grid = [[1,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,1]]
Output: 1
```

Each water cell is isolated, so the best result is a single fish.

**Constraints:**

- `m == grid.length`, `n == grid[i].length`
- `1 <= m, n <= 10`
- `0 <= grid[i][j] <= 10`

---

## Observations

- Water cells form **connected components** via 4-directional adjacency. Because the fisher can freely move between connected water cells, the total fish catchable from a starting cell equals the **sum of all fish in its connected component**.
- Land cells (`grid[r][c] == 0`) act as barriers — the fisher cannot pass through them.
- The answer is the **maximum component sum** across all connected water components.
- Grid size is at most `10 × 10 = 100` cells, so any O(m × n) traversal is trivially fast.
- We can avoid a separate `visited` array by **sinking** visited water cells (setting them to `0` after collecting their fish), reusing the same DFS/BFS pattern as "Max Area of Island".

---

## Solution Explanation

### Approach: DFS with In-Place Marking (Flood Fill)

For every unvisited water cell, launch a DFS that:
1. Accumulates the fish count of every reachable water cell.
2. Marks each visited cell as `0` (land) to prevent re-visiting.

Track the maximum accumulated sum across all DFS calls.

```python
class Solution:
    def findMaxFish(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        def dfs(r, c):
            if r < 0 or r >= m or c < 0 or c >= n:
                return 0
            if grid[r][c] == 0:
                return 0

            fish = grid[r][c]
            grid[r][c] = 0          # Sink the cell (mark visited)
            for nr, nc in [(r+1,c),(r-1,c),(r,c+1),(r,c-1)]:
                fish += dfs(nr, nc)
            return fish

        res = 0
        for r in range(m):
            for c in range(n):
                if grid[r][c] > 0:
                    res = max(res, dfs(r, c))
        return res
```

### Step-by-step

1. **Scan** every cell `(r, c)` in the grid.
2. If the cell is a water cell (`grid[r][c] > 0`), start a **DFS** from it.
3. Inside `dfs(r, c)`:
   - **Base cases:** return `0` if out-of-bounds or the cell is already land/visited.
   - **Collect fish:** save `grid[r][c]`, then **sink** the cell to `0`.
   - **Recurse** in all 4 directions, adding their fish counts.
   - Return the **total fish** in this connected component.
4. Update `res` with the maximum returned by each DFS call.
5. Return `res`.

### Complexity

| | |
|---|---|
| **Time** | O(m × n) — each cell is visited at most once |
| **Space** | O(m × n) — recursion stack depth in the worst case (entire grid is one water region) |

````
