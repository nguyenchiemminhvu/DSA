````markdown
## Problem

https://leetcode.com/problems/find-all-groups-of-farmland/description/

Given a 0-indexed `m x n` binary matrix `land` where `0` represents forested land and `1` represents farmland, find all **rectangular groups** of farmland.

- A **group** is a rectangular area consisting entirely of `1`s.
- No two groups are 4-directionally adjacent to each other.
- Return a 2D array where each entry is `[r1, c1, r2, c2]` — the **top-left** and **bottom-right** corners of each group.

**Example 1:**
```
Input:  land = [[1,0,0],[0,1,1],[0,1,1]]
Output: [[0,0,0,0],[1,1,2,2]]
```

**Example 2:**
```
Input:  land = [[1,1],[1,1]]
Output: [[0,0,1,1]]
```

**Example 3:**
```
Input:  land = [[0]]
Output: []
```

**Constraints:**
- `m == land.length`, `n == land[i].length`
- `1 <= m, n <= 300`
- `land[i][j]` is `0` or `1`
- Groups of farmland are **rectangular** in shape

---

## Observations

1. **Grid is a graph**: Each `1`-cell is a node. Cells connected 4-directionally form a connected component, and the problem guarantees each component is a perfect rectangle.

2. **Guarantee of rectangularity**: Because every group is guaranteed rectangular and no two groups are adjacent, there is no ambiguity — once you locate any `1` in a group, BFS/DFS will collect exactly the cells of that one rectangle.

3. **Only top-left corners matter as starting points**: When scanning row by row, left to right, the first `1` we encounter in a group is always its top-left corner. We don't need to start BFS from any other `1` in the same group.

4. **Bounding box trick**: Instead of storing all visited cells, we only need the **minimum `(r, c)`** and **maximum `(r, c)`** encountered during BFS — those are the top-left and bottom-right corners.

5. **In-place visited marking**: Setting `grid[r][c] = 0` while traversing acts as a visited set, avoiding extra memory and preventing a cell from being enqueued multiple times.

6. **Time Complexity**: `O(m × n)` — each cell is visited at most once across all BFS calls.

7. **Space Complexity**: `O(m × n)` — worst case BFS queue holds all cells (a single giant farmland group).

---

## Solution

### Approach: BFS with Bounding Box Tracking

```python
class Solution:
    def findFarmland(self, grid: List[List[int]]) -> List[List[int]]:
        m, n = len(grid), len(grid[0])
        res = []

        def bfs(r, c):
            tl_r, tl_c = m, n      # top-left initialized to worst case (large)
            br_r, br_c = -1, -1    # bottom-right initialized to worst case (small)
            q = deque([(r, c)])
            grid[r][c] = 0         # mark visited before enqueuing
            while q:
                r, c = q.popleft()
                grid[r][c] = 0
                tl_r = min(tl_r, r)
                tl_c = min(tl_c, c)
                br_r = max(br_r, r)
                br_c = max(br_c, c)
                for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                    if 0 <= nr < m and 0 <= nc < n and grid[nr][nc] == 1:
                        grid[nr][nc] = 0
                        q.append((nr, nc))
            return [tl_r, tl_c, br_r, br_c]

        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1:
                    res.append(bfs(r, c))
        return res
```

### Step-by-step

1. **Outer loop**: Scan every cell `(r, c)` row by row, left to right.
2. **Trigger BFS**: When `grid[r][c] == 1` is found, this cell is the **top-left corner** of an unvisited group. Launch BFS from it.
3. **BFS internals**:
   - Initialize a bounding box: `tl_r = tl_c = ∞` and `br_r = br_c = -∞` (using `m`/`n` and `-1` as sentinels).
   - Mark the starting cell as `0` before enqueuing to prevent duplicate entries.
   - For each dequeued cell `(r, c)`:
     - Mark it `0` (already done before enqueue, but kept for safety).
     - Expand the bounding box by comparing with current `min`/`max` coordinates.
     - Enqueue all 4 valid neighbors that are still `1`, marking them `0` immediately.
4. **Collect result**: After BFS completes, `[tl_r, tl_c, br_r, br_c]` is the exact bounding box of the farmland group. Append it to `res`.
5. **Return** `res` after all cells are processed.

### Why the bounding box always works

Since groups are **guaranteed rectangular**, the minimum row/col seen during BFS is always the top-left corner and the maximum row/col is always the bottom-right corner. No extra geometry check is needed.

### Complexity

| | |
|---|---|
| **Time** | `O(m × n)` — each cell enqueued and dequeued at most once across all BFS calls |
| **Space** | `O(m × n)` — BFS queue in worst case (entire grid is one farmland group) |

---

## Tags

array, matrix, graph, bfs
````
