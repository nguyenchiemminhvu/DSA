## Problem

https://leetcode.com/problems/spiral-matrix-ii/description/

Given a positive integer `n`, generate an `n x n` matrix filled with elements from `1` to `n²` in spiral order.

**Example 1:**
```
Input: n = 3
Output: [[1,2,3],[8,9,4],[7,6,5]]

1 → 2 → 3
            ↓
8 → 9   4
↑       ↓
7 ← 6 ← 5
```

**Example 2:**
```
Input: n = 1
Output: [[1]]
```

**Constraints:** `1 <= n <= 20`

---

## Observations

1. **Spiral traversal has 4 directions in a fixed cycle:** right → down → left → up, repeating indefinitely.
2. **Turn condition:** We need to turn when the next cell would go out of bounds OR has already been filled (non-zero). This is the key insight — previously filled cells act as walls, so no separate "visited" structure is needed.
3. **Termination:** We fill exactly `n²` values, so we loop while `cur_val <= n²`.
4. **At most one valid direction exists:** After filling a cell, there is always at most one valid direction to move. The inner `while` loop cycles through at most 4 turns to find it. If no direction is valid (only possible on the last cell), `count_turn > 4` breaks the loop safely.

---

## Solution Explanation

```python
class Solution:
    def generateMatrix(self, n: int) -> List[List[int]]:
        # right -> down -> left -> up
        dir_r = [ 0, 1, 0, -1 ]
        dir_c = [ 1, 0, -1, 0 ]
        cur_dir = 0

        grid = [[0] * n for _ in range(n)]
        r, c = 0, 0
        cur_val = 1
        while cur_val <= n * n:
            # fill value
            grid[r][c] = cur_val
            cur_val += 1

            # move
            nr = r + dir_r[cur_dir]
            nc = c + dir_c[cur_dir]
            count_turn = 0
            while nr < 0 or nr >= n or nc < 0 or nc >= n or grid[nr][nc] != 0:
                cur_dir = (cur_dir + 1) % 4
                nr = r + dir_r[cur_dir]
                nc = c + dir_c[cur_dir]
                count_turn += 1
                if count_turn > 4:
                    break
            r, c = nr, nc
        
        return grid
```

**Step-by-step walk-through (n = 3):**

| Step | (r, c) | val | Action |
|------|--------|-----|--------|
| 1 | (0,0) | 1 | Fill, move right → (0,1) |
| 2 | (0,1) | 2 | Fill, move right → (0,2) |
| 3 | (0,2) | 3 | Fill, right goes OOB → turn down → (1,2) |
| 4 | (1,2) | 4 | Fill, move down → (2,2) |
| 5 | (2,2) | 5 | Fill, down goes OOB → turn left → (2,1) |
| 6 | (2,1) | 6 | Fill, move left → (2,0) |
| 7 | (2,0) | 7 | Fill, left goes OOB → turn up → (1,0) |
| 8 | (1,0) | 8 | Fill, move up → (0,0), but (0,0)≠0 → turn right → (1,1) |
| 9 | (1,1) | 9 | Fill, `cur_val` = 10 > n² = 9, loop ends |

**Key design choices:**

- **`grid[nr][nc] != 0` as wall check:** Because all cells start at `0` and we fill with values ≥ 1, any already-visited cell acts as a wall. This avoids a separate boolean visited matrix.
- **`count_turn > 4` guard:** After the last cell is filled, all 4 directions are blocked (OOB or filled). The guard prevents an infinite loop by breaking out. The final value of `(nr, nc)` doesn't matter since the outer `while` exits immediately.
- **Direction cycling with `% 4`:** `(cur_dir + 1) % 4` cleanly cycles through the 4 directions without conditionals.

**Complexity:**
- Time: $O(n^2)$ — each cell is visited exactly once.
- Space: $O(1)$ auxiliary (the output matrix itself is required by the problem).
