## Problem

https://leetcode.com/problems/spiral-matrix-iii/description/

You start at the cell `(rStart, cStart)` of a `rows x cols` grid facing east. Walk in a clockwise spiral shape, continuing outside the grid boundary when needed. Return an array of all grid coordinates in the order they are visited.

**Example 1:**
```
Input:  rows = 1, cols = 4, rStart = 0, cStart = 0
Output: [[0,0],[0,1],[0,2],[0,3]]
```

**Example 2:**
```
Input:  rows = 5, cols = 6, rStart = 1, cStart = 4
Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],
         [3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],
         [4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],
         [2,0],[1,0],[0,0]]
```

**Constraints:**
- `1 <= rows, cols <= 100`
- `0 <= rStart < rows`, `0 <= cStart < cols`

---

## Observations

1. **Spiral step pattern.** In a clockwise spiral the directions cycle as: East → South → West → North → East → …  
   The step lengths follow the pattern: **1, 1, 2, 2, 3, 3, 4, 4, …** — each length is repeated exactly twice before increasing by 1.

2. **Walk can leave the grid.** We must keep walking even when we go out of bounds; we simply skip those cells and only collect valid ones. The spiral guarantees we eventually cover every cell.

3. **Step-length increase rule.**  
   - After the 1st direction (East, steps = 1): turn South, keep steps = 1  
   - After the 2nd direction (South, steps = 1): turn West, **increase steps to 2**  
   - After the 3rd direction (West, steps = 2): turn North, keep steps = 2  
   - After the 4th direction (North, steps = 2): turn East, **increase steps to 3**  
   → Steps increase every **2 turns**, specifically after the 3rd direction (index 2) and after completing the full 4-direction loop.

4. **Termination.** We stop as soon as we have collected `rows × cols` cells.

---

## Solution Explanation

### Algorithm

```
Start at (rStart, cStart), add to result.
steps = 1
Loop until result has rows * cols entries:
    For each of the 4 directions (E, S, W, N):
        If this is the 3rd direction (West, index 2): steps += 1
        Walk `steps` steps in this direction,
            appending each cell that is inside the grid.
    steps += 1   ← accounts for the North→East transition
```

The step-length bookkeeping works as follows:

| Turn | Direction | steps used | steps after turn |
|------|-----------|-----------|-----------------|
| 1    | East      | 1          | 1               |
| 2    | South     | 1          | 2 (bumped before West walk) |
| 3    | West      | 2          | 2               |
| 4    | North     | 2          | 3 (bumped at end of loop)   |
| 5    | East      | 3          | 3               |
| …    | …         | …          | …               |

The two increments together implement the "repeat each length twice" rule.

### Code

```python
class Solution:
    def spiralMatrixIII(self, m: int, n: int, r_start: int, c_start: int) -> List[List[int]]:
        res = []

        # 4 directions: right, down, left, up
        dir_r = [ 0,  1,  0, -1]
        dir_c = [ 1,  0, -1,  0]

        r, c = r_start, c_start
        res.append([r, c])

        steps = 1
        while len(res) < m * n:
            for d in range(4):
                dr, dc = dir_r[d], dir_c[d]

                if d == 2:          # before walking West, increase step length
                    steps += 1

                for _ in range(steps):
                    r += dr
                    c += dc
                    if 0 <= r < m and 0 <= c < n:
                        res.append([r, c])

            steps += 1              # after full round (N→E), increase again

        return res
```

### Complexity

| | |
|---|---|
| **Time** | O(max(rows, cols)²) — the spiral radius grows until it covers the farthest corner |
| **Space** | O(rows × cols) — the result array |
