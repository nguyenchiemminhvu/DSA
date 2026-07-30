````markdown
## Problem

https://leetcode.com/problems/making-a-large-island/description/

You are given an `n x n` binary matrix `grid`. You are allowed to change **at most one** `0` to `1`.

Return the **size of the largest island** in `grid` after applying this operation.

An **island** is a 4-directionally connected group of `1`s.

**Examples:**

```
Input: grid = [[1,0],[0,1]]   → Output: 3
Input: grid = [[1,1],[1,0]]   → Output: 4
Input: grid = [[1,1],[1,1]]   → Output: 4
```

**Constraints:** `1 <= n <= 500`, `grid[i][j]` is `0` or `1`.

---

## Observations

- A naive approach would flip each `0` to `1`, then run a full BFS/DFS to find the largest island — but that is **O(n⁴)**, too slow for `n = 500`.
- The key insight is that flipping a single `0` can **merge the islands of its (up to 4) land neighbors**. The resulting island size is:
  ```
  1  +  sum of sizes of distinct neighboring islands
  ```
- We can **pre-compute the size of every island** in the original grid in a single BFS/DFS pass, assigning each island a unique label (color/ID).
- Then, for every `0` cell, we look at its 4 neighbors, collect the **distinct island IDs**, sum their sizes, add 1 (the flipped cell itself), and track the maximum.
- Edge case: if the grid has **no `0`s at all**, the answer is `n × n` (the whole grid is already one island after any flip is skipped).

---

## Solution Explanation

### Approach: Island Labeling + Single-Pass Evaluation

#### Step 1 — Label every island and record its size

Run a DFS/BFS over the grid. Whenever an unvisited `1` is found, flood-fill it with a unique integer ID (starting from `2` to avoid clash with `0` and `1`). Store `island_size[id] = area` in a map.

#### Step 2 — Evaluate every `0` cell

For each cell `(r, c)` where `grid[r][c] == 0`:
- Collect the IDs of its distinct 4-directional neighbors (ignore out-of-bounds and water).
- Candidate size = `1 + sum(island_size[id] for id in distinct_neighbor_ids)`.
- Update the global maximum.

#### Step 3 — Handle the all-land grid

If no `0` was ever processed, the answer is `n * n`.

```python
class Solution:
    def largestIsland(self, grid: List[List[int]]) -> int:
        n = len(grid)
        island_size = {}
        color = 2  # IDs start at 2 (0 and 1 are reserved)

        def dfs(r, c, col):
            if r < 0 or r >= n or c < 0 or c >= n or grid[r][c] != 1:
                return 0
            grid[r][c] = col
            size = 1
            for dr, dc in [(1,0),(-1,0),(0,1),(0,-1)]:
                size += dfs(r + dr, c + dc, col)
            return size

        # Step 1: label all islands
        for r in range(n):
            for c in range(n):
                if grid[r][c] == 1:
                    island_size[color] = dfs(r, c, color)
                    color += 1

        # Step 2: try flipping each 0
        res = max(island_size.values(), default=0)  # covers all-land case
        for r in range(n):
            for c in range(n):
                if grid[r][c] == 0:
                    seen = set()
                    for dr, dc in [(1,0),(-1,0),(0,1),(0,-1)]:
                        nr, nc = r + dr, c + dc
                        if 0 <= nr < n and 0 <= nc < n and grid[nr][nc] > 1:
                            seen.add(grid[nr][nc])
                    res = max(res, 1 + sum(island_size[id] for id in seen))

        return res
```

### Step-by-step walkthrough (Example 1: `[[1,0],[0,1]]`)

| Stage | Grid state |
|---|---|
| Label island at (0,0) with ID=2, size=1 | `[[2,0],[0,1]]` |
| Label island at (1,1) with ID=3, size=1 | `[[2,0],[0,3]]` |
| Flip (0,1)=0: neighbors → ID=2 (left) + ID=3 (down) → 1+1+1=**3** | ✓ |
| Flip (1,0)=0: neighbors → ID=2 (up) + ID=3 (right) → 1+1+1=**3** | ✓ |
| Answer: **3** | |

### Complexity

| | |
|---|---|
| **Time** | O(n²) — each cell is visited a constant number of times |
| **Space** | O(n²) — for the island size map and recursion stack |
````
