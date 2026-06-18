## Problem

https://leetcode.com/problems/unique-paths-iii/description/

You are given an `m x n` integer grid where each cell is one of:
- `1` — the **starting** square (exactly one)
- `2` — the **ending** square (exactly one)
- `0` — an **empty** square you can walk over
- `-1` — an **obstacle** you cannot walk over

Return the number of **4-directional walks** from the starting square to the ending square that **walk over every non-obstacle square exactly once**.

---

## Observations

1. **Every non-obstacle square must be visited exactly once.**  
   Non-obstacle squares are: the start (`1`), the end (`2`), and all empty squares (`0`).  
   Obstacles (`-1`) are simply skipped.

2. **The condition for a valid path:**  
   A path is valid when we arrive at the end cell (`2`) having already stepped on every empty (`0`) cell exactly once.  
   Since the start cell is visited before DFS begins and the end cell is reached by arriving at it, we only need to count the empty (`0`) cells as a coverage metric.

3. **Backtracking is required.**  
   We must explore all possible paths. After visiting a cell and recursing into it, we must **unmark** it (backtrack) so other branches can use it — this is a classic DFS + backtracking pattern.

4. **Small grid constraint enables brute-force DFS.**  
   The constraint `1 <= m * n <= 20` means there are at most 20 cells total. The number of possible paths is bounded, so an exhaustive DFS with backtracking is efficient enough.

5. **`cover` tracks only the empty (`0`) cells visited so far.**  
   - The start cell is pre-marked `visited` before DFS begins — no need to count it.  
   - The end cell is the DFS base case — we check coverage when we land on it.  
   - So `cover` needs only to count `0`-cells stepped on along the way.

---

## Solution Explanation

```python
class Solution:
    def uniquePathsIII(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        start_r, start_c = -1, -1
        total_empty = 0
        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1:
                    start_r, start_c = r, c
                elif grid[r][c] == 0:
                    total_empty += 1

        visited = [[False] * n for _ in range(m)]
        visited[start_r][start_c] = True

        def dfs(r, c, cover):
            if grid[r][c] == 2:
                return 1 if cover == total_empty else 0
            
            res = 0
            for nr, nc in [(r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)]:
                if nr >= 0 and nr < m and nc >= 0 and nc < n:
                    if not visited[nr][nc] and grid[nr][nc] != -1:
                        visited[nr][nc] = True
                        next_cover = cover + 1 if grid[nr][nc] == 0 else cover
                        res += dfs(nr, nc, next_cover)
                        visited[nr][nc] = False
            return res
        
        count = dfs(start_r, start_c, 0)
        return count
```

### Step-by-step walkthrough

**1. Preprocessing (scan the grid)**
- Find the start cell `(start_r, start_c)` where `grid[r][c] == 1`.
- Count `total_empty`: the number of `0`-cells. This is the target coverage we must reach.

**2. Initialize visited**
- Mark the start cell as visited immediately so DFS branches never revisit it.

**3. DFS with backtracking — `dfs(r, c, cover)`**
- **Base case:** If the current cell is `2` (end), check if `cover == total_empty`.  
  - `True` → this path visited all empty squares → return `1` (count this valid path).  
  - `False` → arrived at end too early, some empty squares were skipped → return `0`.
- **Recursive case:** Try all 4 neighbors `(nr, nc)`.  
  - Skip if out of bounds, already visited, or an obstacle.  
  - Mark `(nr, nc)` as visited.  
  - If the neighbor is `0`, increment `cover` (we are stepping on a new empty cell).  
  - Recurse into the neighbor and accumulate the result.  
  - **Backtrack:** unmark `(nr, nc)` so other paths can use it.

**4. Return the total count.**

---

### Complexity

| | Complexity |
|---|---|
| **Time** | $O(4^{m \cdot n})$ — at most $4$ choices per step, up to $m \cdot n$ steps deep |
| **Space** | $O(m \cdot n)$ — recursion depth + visited array |

In practice, the backtracking prunes heavily, and the constraint $m \cdot n \le 20$ keeps it fast.

---

### Key insight

The `cover` counter elegantly bridges the two requirements of the problem:
1. **Reach the end** — ensured by the `grid[r][c] == 2` base case.
2. **Visit every empty square** — ensured by `cover == total_empty`.

Only when *both* conditions hold simultaneously is the path counted as valid.
