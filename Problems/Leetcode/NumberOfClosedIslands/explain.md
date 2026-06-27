## Problem

https://leetcode.com/problems/number-of-closed-islands/description/

Given a 2D `grid` of `0s` (land) and `1s` (water), an *island* is a maximal 4-directionally connected group of `0s`. A *closed island* is an island **totally** surrounded by `1s` on all sides (left, top, right, bottom).

Return the number of *closed islands*.

**Constraints:**
- `1 <= grid.length, grid[0].length <= 100`
- `0 <= grid[i][j] <= 1`

---

## Solution

### Intuition

An island is *not* closed if any of its cells touches the border of the grid (row 0, last row, column 0, or last column) — it can "leak" out. So the problem reduces to:

> Count the number of land-connected components that have **no cell on the border**.

### Approach — BFS Flood Fill

For each unvisited land cell (`0`), run a BFS to explore the entire connected island:

1. **Mark visited** cells as `2` during traversal to avoid re-processing.
2. **Track validity**: if any cell in the island sits on the grid border, the island is not closed (`valid = False`).
3. After the BFS, if the island was fully interior (`valid = True`), increment the result.

Key detail: the BFS **always completes the full traversal** before returning, even if an out-of-bounds cell is found. This ensures all cells in the island get marked as visited so they are not double-counted by future BFS calls.

### Walkthrough (Example 1)

```
1 1 1 1 1 1 1 0
1 0 0 0 0 1 1 0
1 0 1 0 1 1 1 0
1 0 0 0 0 1 0 1
1 1 1 1 1 1 1 0
```

- The large `0`-group in the middle-left is fully surrounded by `1s` → **closed**.
- The single `0` at row 3, col 6 is interior → **closed**.
- All `0s` on the rightmost column touch the border → **not closed**, discarded.

Result: `2`

### Complexity

| | |
|---|---|
| Time | $O(m \times n)$ — each cell is visited at most once |
| Space | $O(m \times n)$ — BFS queue in the worst case (one large island) |

### Code

```python
from collections import deque
from typing import List

class Solution:
    def closedIsland(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        def bfs(r, c):
            valid = True
            q = deque([(r, c)])
            while q:
                r, c = q.popleft()
                # touching the border means this island is open
                if r == 0 or r == m - 1 or c == 0 or c == n - 1:
                    valid = False
                grid[r][c] = 2  # mark visited
                for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                    if 0 <= nr < m and 0 <= nc < n and grid[nr][nc] == 0:
                        q.append((nr, nc))
            return valid

        res = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 0:
                    if bfs(i, j):
                        res += 1
        return res
```

### Why `valid` is not returned early

It might be tempting to `return False` as soon as a border cell is found, but that would leave neighboring `0s` **unvisited**. Those cells would then trigger a new BFS on the next outer loop iteration, incorrectly counting a portion of the same island as a separate (possibly closed) island.

By always completing the full BFS and only tracking `valid` as a flag, every cell in each island is consumed exactly once.
