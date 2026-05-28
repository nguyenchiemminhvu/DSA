## Problem

https://leetcode.com/problems/largest-1-bordered-square/description

Given a 2D grid of `0`s and `1`s, return the number of elements in the largest square subgrid that has **all `1`s on its border**, or `0` if such a subgrid doesn't exist in the grid.

**Example 1:**
```
Input:  grid = [[1,1,1],[1,0,1],[1,1,1]]
Output: 9
```

**Example 2:**
```
Input:  grid = [[1,1,0,0]]
Output: 1
```

**Constraints:**
- `1 <= grid.length <= 100`
- `1 <= grid[0].length <= 100`
- `grid[i][j]` is `0` or `1`

---

## Observations

- A valid bordered square of side `k` anchored at top-left corner `(i, j)` requires:
  - The **top** row    : `k` consecutive `1`s going right  from `(i, j)`
  - The **left** column: `k` consecutive `1`s going down   from `(i, j)`
  - The **bottom** row : `k` consecutive `1`s going right  from `(i+k-1, j)`
  - The **right** column: `k` consecutive `1`s going down  from `(i, j+k-1)`
- Interior cells are irrelevant — only the **four borders** need to be all `1`s.
- Naively checking all four borders for every `(i, j, k)` triplet costs O(n³ · n) = O(n⁴). We can reduce border checking to **O(1)** by pre-computing two auxiliary matrices:
  - `right[i][j]` — number of consecutive `1`s to the **right** starting at `(i, j)` (including itself).
  - `down[i][j]`  — number of consecutive `1`s **downward** starting at `(i, j)` (including itself).
- With these tables the four border conditions become simple comparisons, bringing the overall complexity to **O(n³)**.
- We iterate `k` from `min(m, n)` down to `1` and return immediately when the first valid square is found, giving the largest possible answer.

---

## Solution

```python
class Solution:
    def largest1BorderedSquare(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        # --- Step 1: build auxiliary tables ---
        # right[i][j] = consecutive 1s going right from (i, j), inclusive
        # down[i][j]  = consecutive 1s going down  from (i, j), inclusive
        right = [[0] * n for _ in range(m)]
        down  = [[0] * n for _ in range(m)]

        # Fill from bottom-right to top-left so each cell can reference
        # the already-computed value of its right / lower neighbour.
        for i in range(m - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                if grid[i][j] == 1:
                    right[i][j] = 1 + (right[i][j + 1] if j + 1 < n else 0)
                    down[i][j]  = 1 + (down[i + 1][j]  if i + 1 < m else 0)

        # --- Step 2: search for the largest valid bordered square ---
        # Try every possible side length k from largest to smallest.
        for k in range(min(m, n), 0, -1):
            for i in range(m - k + 1):          # valid top rows
                for j in range(n - k + 1):      # valid left columns
                    # Check all four borders in O(1) using the precomputed tables:
                    #   top border    : right[i][j]         >= k
                    #   left border   : down[i][j]          >= k
                    #   bottom border : right[i + k - 1][j] >= k
                    #   right border  : down[i][j + k - 1]  >= k
                    if (right[i][j]         >= k and
                        down[i][j]          >= k and
                        right[i + k - 1][j] >= k and
                        down[i][j + k - 1]  >= k):
                        return k * k   # first hit is the largest square

        return 0  # no bordered square found
```

### Walkthrough on Example 1

```
grid:          right:         down:
1 1 1          3 2 1          3 1 3
1 0 1          1 0 1          2 0 2
1 1 1          3 2 1          1 1 1
```

Check `k = 3`, top-left `(0, 0)`:
- `right[0][0] = 3 >= 3` ✓  (top border)
- `down[0][0]  = 3 >= 3` ✓  (left border)
- `right[2][0] = 3 >= 3` ✓  (bottom border)
- `down[0][2]  = 3 >= 3` ✓  (right border)

All four conditions satisfied → return `3 × 3 = 9`.

### Complexity

| | |
|---|---|
| **Time**  | O(m · n) to build tables + O(min(m,n) · m · n) for search = **O(n³)** |
| **Space** | O(m · n) for the two auxiliary matrices |
