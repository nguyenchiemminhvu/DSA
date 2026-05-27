## Problem

https://leetcode.com/problems/as-far-from-land-as-possible/description

````markdown
## Problem

https://leetcode.com/problems/as-far-from-land-as-possible/description

Given an `n x n` grid containing only values `0` and `1`, where `0` represents water and `1` represents land, find a **water cell** such that its distance to the nearest land cell is **maximized**, and return that distance. If no land or water exists in the grid, return `-1`.

The distance used is the **Manhattan distance**: the distance between two cells `(x0, y0)` and `(x1, y1)` is `|x0 - x1| + |y0 - y1|`.

**Example 1:**
```
Input:  grid = [[1,0,1],[0,0,0],[1,0,1]]
Output: 2
Explanation: Cell (1,1) is distance 2 from every land cell.
```

**Example 2:**
```
Input:  grid = [[1,0,0],[0,0,0],[0,0,0]]
Output: 4
Explanation: Cell (2,2) is distance 4 from the only land cell at (0,0).
```

**Constraints:**
- `n == grid.length == grid[i].length`
- `1 <= n <= 100`
- `grid[i][j]` is `0` or `1`

## Observations

1. **Edge cases first:** If the grid is all land (`1`s) or all water (`0`s), there is no valid water-land pair, so we return `-1` immediately.

2. **Multi-source BFS is the key insight:** Instead of running BFS from every water cell to find the nearest land (which would be $O(n^4)$), we flip the perspective: start BFS simultaneously from **all land cells at once**. Each BFS "wave" expands one step outward, marking water cells with increasing distances. The last water cell to be reached holds the maximum distance.

3. **Why simultaneous expansion works:** Because all land cells start at distance `0` in the queue, the BFS wavefront expands uniformly. A water cell is first visited exactly when the shortest path from any land cell reaches it — precisely the Manhattan distance to the nearest land cell. This is the classic **multi-source BFS** technique.

4. **Distance tracking without an extra array:** Rather than maintaining a separate distance matrix, we reuse the grid itself. When a water cell (`0`) is first reached by the BFS, we mark it as `1` to avoid revisiting it, and we track "distance" by counting BFS levels (each full level processed = distance increments by 1).

5. **Time and space complexity:**
   - **Time:** $O(n^2)$ — every cell is enqueued and processed at most once.
   - **Space:** $O(n^2)$ — the BFS queue can hold up to all cells in the worst case.

## Solution

```python
from collections import deque
from typing import List

class Solution:
    def maxDistance(self, grid: List[List[int]]) -> int:
        n = len(grid)

        # Step 1: Seed the BFS queue with every land cell
        q = deque()
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    q.append((i, j))

        # Edge case: all land or all water → no valid answer
        if not q or len(q) == n * n:
            return -1

        # Step 2: Multi-source BFS expanding outward from all land cells
        dist = -1
        while q:
            # Each iteration of the outer loop = one BFS level = distance +1
            dist += 1
            for _ in range(len(q)):
                r, c = q.popleft()
                for nr, nc in [(r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)]:
                    if 0 <= nr < n and 0 <= nc < n and grid[nr][nc] == 0:
                        grid[nr][nc] = 1   # mark visited
                        q.append((nr, nc))

        # dist now holds the level at which the last water cell was first reached
        return dist
```

**Step-by-step walkthrough (Example 2: `grid = [[1,0,0],[0,0,0],[0,0,0]]`):**

| BFS Level | Queue contents (cells reached this wave) | `dist` after level |
|-----------|------------------------------------------|--------------------|
| Init      | `(0,0)` — the single land cell           | `-1`               |
| Level 0   | Process `(0,0)` → reach `(0,1)`, `(1,0)` | `0`               |
| Level 1   | Process `(0,1)`, `(1,0)` → reach `(0,2)`, `(1,1)`, `(2,0)` | `1` |
| Level 2   | Process `(0,2)`, `(1,1)`, `(2,0)` → reach `(1,2)`, `(2,1)` | `2` |
| Level 3   | Process `(1,2)`, `(2,1)` → reach `(2,2)` | `3` |
| Level 4   | Process `(2,2)` → no new cells           | `4` |

Final answer: **4** ✓

**Complexity:**
- **Time:** $O(n^2)$
- **Space:** $O(n^2)$

# Tags
- Graph
- Breadth-First Search (BFS)
- Multi-source BFS
- Matrix
````
