## Problem

https://leetcode.com/problems/find-the-safest-path-in-a-grid

You are given a 0-indexed `n x n` grid where each cell is either `0` (empty) or `1` (thief). Starting at `(0, 0)`, you can move to any adjacent cell (up, down, left, right). The **safeness factor** of a path is the **minimum Manhattan distance** from any cell on that path to any thief in the grid. Return the **maximum safeness factor** over all possible paths from `(0, 0)` to `(n-1, n-1)`.

---

## Observations

1. **Edge case**: If `(0, 0)` or `(n-1, n-1)` contains a thief, any path must pass through a thief cell, so the answer is `0`.

2. **Manhattan distance pre-computation**: For every cell we need to know its distance to the nearest thief. Computing this naively (per cell, scan all thieves) would be $O(n^4)$. Instead, a **multi-source BFS** launched simultaneously from all thief cells fills the entire grid in $O(n^2)$ — each cell `dp[r][c]` ends up holding the minimum Manhattan distance to the nearest thief.

3. **Monotonicity property**: If there exists a valid path with safeness factor $\ge k$, then there also exists a valid path with safeness factor $\ge k-1$. Conversely, if no such path exists for $k$, none exists for $k+1$ either. This monotonic structure makes **binary search** on the answer applicable.

4. **Feasibility check**: Given a candidate safeness value `mid`, we only need to check whether `(0, 0)` can reach `(n-1, n-1)` by walking only through cells where `dp[r][c] >= mid`. A simple BFS/DFS on the filtered graph answers this in $O(n^2)$.

5. **Binary search bounds**: The answer lies in `[0, max_safeness]`, where `max_safeness` is the largest distance value in the `dp` table (found for free during the multi-source BFS).

---

## Solution Walkthrough

### Step 1 — Multi-source BFS to build the distance table

All thief cells are seeded into a queue with distance `0`. BFS expands outward layer by layer, setting `dp[r][c]` to the shortest distance to any thief. The BFS visits each cell at most once, so this step is $O(n^2)$.

```
grid = [[0,0,1],        dp after BFS:
        [0,0,0],    →   [[2,1,0],
        [0,0,0]]         [2,2,1],
                         [3,3,2]]
```

### Step 2 — Binary search on safeness factor

We binary search over `[0, max_safeness]`:
- **Mid is feasible** → record `res = mid`, search higher (`left = mid + 1`).
- **Mid is infeasible** → search lower (`right = mid - 1`).

### Step 3 — Feasibility BFS

For a given `target`, start BFS from `(0, 0)` and only enqueue a neighbor `(nr, nc)` if `dp[nr][nc] >= target`. If `(n-1, n-1)` is reached, the target is achievable.

---

## Complexity

| Phase | Time | Space |
|---|---|---|
| Multi-source BFS | $O(n^2)$ | $O(n^2)$ |
| Binary search iterations | $O(\log n)$ | — |
| Each feasibility BFS | $O(n^2)$ | $O(n^2)$ |
| **Total** | $O(n^2 \log n)$ | $O(n^2)$ |

---

## Annotated Code

```python
from collections import deque
from typing import List

class Solution:
    def maximumSafenessFactor(self, grid: List[List[int]]) -> int:
        n = len(grid)

        # Edge case: start or end is a thief cell
        if grid[0][0] == 1 or grid[n-1][n-1] == 1:
            return 0

        INF = 0xFFFFFFFF
        dp = [[INF] * n for _ in range(n)]
        q = deque()

        # Seed BFS from every thief cell simultaneously
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    dp[i][j] = 0
                    q.append((0, i, j))

        # Multi-source BFS: fill dp[r][c] = min distance to nearest thief
        max_safeness = 0
        while q:
            d, r, c = q.popleft()
            max_safeness = max(max_safeness, d)
            for nr, nc in [(r+1,c),(r-1,c),(r,c+1),(r,c-1)]:
                if 0 <= nr < n and 0 <= nc < n:
                    if grid[nr][nc] == 0 and dp[nr][nc] > d + 1:
                        dp[nr][nc] = d + 1
                        q.append((d + 1, nr, nc))

        # Check if (0,0) → (n-1,n-1) exists using only cells with dp >= target
        def can_reach_end(target: int) -> bool:
            if dp[0][0] < target:
                return False

            q = deque([(0, 0)])
            visited = [[False] * n for _ in range(n)]
            visited[0][0] = True

            while q:
                r, c = q.popleft()
                if r == n-1 and c == n-1:
                    return True
                for nr, nc in [(r+1,c),(r-1,c),(r,c+1),(r,c-1)]:
                    if 0 <= nr < n and 0 <= nc < n and not visited[nr][nc]:
                        if dp[nr][nc] >= target:
                            visited[nr][nc] = True
                            q.append((nr, nc))
            return False

        # Binary search on the answer
        left, right = 0, max_safeness
        res = 0

        while left <= right:
            mid = left + (right - left) // 2
            if can_reach_end(mid):
                res = mid        # mid is valid, try to do better
                left = mid + 1
            else:
                right = mid - 1  # mid is too strict, relax

        return res
```

---

## Dry Run — Example 2

```
grid = [[0,0,1],
        [0,0,0],
        [0,0,0]]
```

**After multi-source BFS:**
```
dp = [[2,1,0],
      [2,2,1],
      [3,3,2]]
max_safeness = 3
```

**Binary search:**
| Iteration | left | right | mid | can_reach_end(mid) | res |
|-----------|------|-------|-----|-------------------|-----|
| 1 | 0 | 3 | 1 | True (path via dp≥1) | 1 |
| 2 | 2 | 3 | 2 | True (path via dp≥2) | 2 |
| 3 | 3 | 3 | 3 | False (dp[2][2]=2 < 3) | 2 |

**Output: 2** ✓
