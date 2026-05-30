## Problem

https://leetcode.com/problems/shortest-path-in-binary-matrix/description/

Given an `n x n` binary matrix `grid`, return the length of the shortest **clear path** from the top-left cell `(0, 0)` to the bottom-right cell `(n-1, n-1)`. If no such path exists, return `-1`.

A **clear path** requires:
- Every visited cell has value `0`.
- Adjacent cells are **8-directionally** connected (share an edge or corner).

The **length** of the path is the total number of visited cells (including start and end).

**Examples:**
```
grid = [[0,1],[1,0]]  → 2       (only path: (0,0) → (1,1))
grid = [[0,0,0],[1,1,0],[1,1,0]] → 4   (path visits 4 cells)
grid = [[1,0,0],[1,1,0],[1,1,0]] → -1  (start cell is blocked)
```

---

## Observations

1. **Shortest path on an unweighted graph → BFS.**  
   Each cell is a node; edges exist between any two 8-directionally adjacent cells that are both `0`. We want the minimum number of nodes on a path from `(0,0)` to `(n-1,n-1)`. BFS explores nodes level-by-level, so the first time we reach the destination is guaranteed to be the shortest path.

2. **Early termination at the source.**  
   If `grid[0][0] == 1`, no path can ever start, so return `-1` immediately.

3. **Mark visited on enqueue, not on dequeue.**  
   Adding `(nr, nc)` to `visited` the moment it is pushed into the queue prevents other cells from enqueuing the same cell again before it is processed, avoiding redundant work and potential cycles.

4. **Path length = BFS depth (steps), not edges.**  
   Because the problem counts *visited cells* (not edges), the answer is the BFS level at which `(n-1, n-1)` is first found. We start `steps = 0` and increment it at the beginning of each level's processing, so when we dequeue the destination it already reflects the correct count.

5. **Grid boundary check is necessary.**  
   Since we explore all 8 neighbours, indices can go out of `[0, n)` and must be filtered before accessing `grid`.

---

## Solution

```python
from collections import deque
from typing import List

class Solution:
    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        n = len(grid)
        if grid[0][0] == 1:          # (Observation 2) source is blocked
            return -1

        q = deque([(0, 0)])
        visited = set()
        visited.add((0, 0))          # (Observation 3) mark on enqueue

        steps = 0
        while q:
            length = len(q)
            steps += 1               # (Observation 4) entering a new BFS level
            for _ in range(length):
                r, c = q.popleft()
                if r == n - 1 and c == n - 1:
                    return steps     # first time we reach destination = shortest

                adjs = [
                    (r + 1, c),
                    (r - 1, c),
                    (r, c + 1),
                    (r, c - 1),
                    (r - 1, c - 1),
                    (r - 1, c + 1),
                    (r + 1, c - 1),
                    (r + 1, c + 1),
                ]
                for nr, nc in adjs:
                    if nr < 0 or nr >= n or nc < 0 or nc >= n:  # (Observation 5)
                        continue
                    if (nr, nc) in visited:
                        continue
                    if grid[nr][nc] == 0:
                        visited.add((nr, nc))   # (Observation 3) mark on enqueue
                        q.append((nr, nc))

        return -1   # queue exhausted without reaching destination
```

**Complexity:**
- **Time:** $O(n^2)$ — each cell is enqueued and dequeued at most once.
- **Space:** $O(n^2)$ — the `visited` set and queue can hold at most all $n^2$ cells.
