## Problem

https://leetcode.com/problems/find-a-safe-walk-through-a-grid/description/

```
You are given an m x n binary matrix grid and an integer health.

You start on the upper-left corner (0, 0) and would like to get to the lower-right corner (m - 1, n - 1).

You can move up, down, left, or right from one cell to another adjacent cell as long as your health remains positive.

Cells (i, j) with grid[i][j] = 1 are considered unsafe and reduce your health by 1.

Return true if you can reach the final cell with a health value of 1 or more, and false otherwise.
```

**Example 1:**
```
Input:  grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1
Output: true
```

**Example 2:**
```
Input:  grid = [[0,1,1,0,0,0],[1,0,1,0,0,0],[0,1,1,1,0,1],[0,0,1,0,1,0]], health = 3
Output: false
Explanation: A minimum of 4 health points is needed to reach the final cell safely.
```

**Example 3:**
```
Input:  grid = [[1,1,1],[1,0,1],[1,1,1]], health = 5
Output: true
Explanation: The only safe path goes through (1,1), consuming exactly 4 health points.
```

**Constraints:**
- `m == grid.length`, `n == grid[i].length`
- `1 <= m, n <= 50`, `2 <= m * n`
- `1 <= health <= m + n`
- `grid[i][j]` is either `0` or `1`

---

## Observations

1. **Reframe as a shortest-path problem**: Instead of asking *"can I survive with the given health?"*, ask *"what is the minimum health consumed on any path from `(0,0)` to `(m-1,n-1)`?"* The answer to the original question is then simply: `min_cost < health`.

2. **Binary edge weights (0 or 1)**: Every move into a cell costs exactly `grid[i][j]` — either `0` (safe, free) or `1` (unsafe, costs one health point). This is a weighted shortest-path problem, but the weights are restricted to `{0, 1}`.

3. **0-1 BFS over Dijkstra**: When edge weights are only 0 or 1, a deque-based **0-1 BFS** finds the shortest path in `O(V + E)` — faster than Dijkstra's `O(E log V)`. The key rule is:
   - Moving into a **free cell** (cost 0) → push to the **front** of the deque (same priority level).
   - Moving into an **unsafe cell** (cost 1) → push to the **back** of the deque (higher cost level).
   
   This preserves the monotonically non-decreasing ordering of costs at the front of the deque, mimicking a priority queue without the log factor overhead.

4. **Why not standard BFS?**: Standard BFS finds the path with the fewest hops, not the path with the lowest total cost. Two paths with the same number of steps can have very different health costs depending on how many unsafe cells they pass through. We need cost-aware traversal.

5. **DP state**: `dp[i][j]` = the minimum number of unsafe cells encountered on **any** path from `(0,0)` to `(i,j)`. We update `dp[nr][nc]` only when we find a strictly cheaper path:
   ```
   if dp[r][c] + grid[nr][nc] < dp[nr][nc]:
       dp[nr][nc] = dp[r][c] + grid[nr][nc]
   ```

6. **Starting cost**: The starting cell `(0,0)` may itself be unsafe (`grid[0][0] = 1`), so `dp[0][0] = grid[0][0]`, not `0`.

7. **Final check**: After the 0-1 BFS settles, `dp[m-1][n-1]` holds the minimum health consumed to reach the destination. We return `dp[m-1][n-1] < health` (we need at least 1 health remaining, so strictly less than).

---

## Solution

### Approach: 0-1 BFS (Deque-based Shortest Path)

**Algorithm:**
1. Initialize `dp[i][j] = INF` for all cells, `dp[0][0] = grid[0][0]`.
2. Push `(0, 0)` onto the deque.
3. While the deque is not empty:
   - Pop `(r, c)` from the **front**.
   - For each valid neighbor `(nr, nc)`:
     - Compute `new_cost = dp[r][c] + grid[nr][nc]`.
     - If `new_cost < dp[nr][nc]`: update `dp[nr][nc] = new_cost`, then:
       - If `grid[nr][nc] == 0` → push `(nr, nc)` to the **front** (zero-cost move).
       - If `grid[nr][nc] == 1` → push `(nr, nc)` to the **back** (unit-cost move).
4. Return `dp[m-1][n-1] < health`.

---

**Walkthrough** — Example 3: `grid = [[1,1,1],[1,0,1],[1,1,1]]`, `health = 5`

```
Grid:           dp (initial):
1  1  1         INF  INF  INF
1  0  1    →    INF  INF  INF
1  1  1         INF  INF  INF

dp[0][0] = grid[0][0] = 1,  deque: [(0,0)]
```

| Step | Pop    | dp[r][c] | Neighbor | new_cost | Action                |
|------|--------|----------|----------|----------|-----------------------|
| 1    | (0,0)  | 1        | (1,0)    | 1+1=2    | push back             |
|      |        |          | (0,1)    | 1+1=2    | push back             |
| 2    | (1,0)  | 2        | (2,0)    | 2+1=3    | push back             |
|      |        |          | (1,1)    | 2+0=2    | push **front**        |
| 3    | (1,1)  | 2        | (2,1)    | 2+1=3    | push back             |
|      |        |          | (1,2)    | 2+1=3    | push back             |
| 4    | (0,1)  | 2        | (0,2)    | 2+1=3    | push back             |
| 5    | (2,0)  | 3        | (2,1)    | 4 > 3    | skip                  |
| 6    | (2,1)  | 3        | (2,2)    | 3+1=4    | push back             |
| 7    | (1,2)  | 3        | (2,2)    | 4 ≥ 4    | skip (no improvement) |
| 8    | (0,2)  | 3        | (1,2)    | 4 > 3    | skip                  |
| 9    | (2,2)  | 4        | —        | —        | done                  |

```
dp (final):
1  2  3
2  2  3
3  3  4

dp[2][2] = 4 < 5 = health  →  True ✓
```

The minimum-cost path is `(0,0)→(1,0)→(1,1)→(1,2)→(2,2)`, consuming 4 health points. Since `4 < 5`, we arrive with 1 health remaining.

---

**Code:**
```python
from collections import deque
from typing import List

class Solution:
    def findSafeWalk(self, grid: List[List[int]], health: int) -> bool:
        INF = 0xFFFFFFFF
        m, n = len(grid), len(grid[0])

        dp = [[INF] * n for _ in range(m)]
        dp[0][0] = grid[0][0]
        q = deque([(0, 0)])
        while q:
            r, c = q.popleft()
            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                if 0 <= nr < m and 0 <= nc < n:
                    cost = grid[nr][nc]
                    if dp[r][c] + cost < dp[nr][nc]:
                        dp[nr][nc] = dp[r][c] + cost
                        if cost == 0:
                            q.appendleft((nr, nc))  # free move → front
                        else:
                            q.append((nr, nc))       # costly move → back

        return dp[m - 1][n - 1] < health
```

---

## Complexity

**Time Complexity**: `O(m × n)`  
Each cell is processed at most twice in 0-1 BFS (once from a cost-0 edge, once from a cost-1 edge). With `V = m*n` cells and `E = O(m*n)` edges, total work is `O(m*n)`.

**Space Complexity**: `O(m × n)`  
For the `dp` table and the deque, both bounded by the number of cells.

---

## Tags

`BFS`, `0-1 BFS`, `Shortest Path`, `Dynamic Programming`, `Graph`, `Matrix`
