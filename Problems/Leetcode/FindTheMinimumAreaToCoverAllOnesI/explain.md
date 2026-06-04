## Problem

https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-i/

Given a 2D binary array `grid`, find the smallest axis-aligned rectangle (with horizontal and vertical sides) such that all `1`s in the grid lie inside it. Return its minimum possible area.

---

## Observations

- An axis-aligned bounding rectangle is fully defined by four values: the **minimum and maximum row** indices and the **minimum and maximum column** indices among all cells containing `1`.
- The area is simply `(max_row - min_row + 1) * (max_col - min_col + 1)`.
- We only need a single pass over every cell to compute these four boundary values.
- The problem guarantees at least one `1` exists, so we never have to handle the empty case.

---

## Solution Explanation

```python
class Solution:
    def minimumArea(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        min_row = m
        max_row = -1
        min_col = n
        max_col = -1
        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1:
                    min_row = min(min_row, r)
                    max_row = max(max_row, r)
                    min_col = min(min_col, c)
                    max_col = max(max_col, c)

        return (max_row - min_row + 1) * (max_col - min_col + 1)
```

**Step-by-step:**

1. Initialize the four boundary trackers to sentinel values (`min_row = m`, `max_row = -1`, etc.).
2. Iterate over every cell `(r, c)`. When a `1` is found, update all four boundaries.
3. After the scan, the bounding rectangle spans rows `[min_row, max_row]` and columns `[min_col, max_col]`.
4. Return the rectangle's area.

| Variable  | Tracks                          |
|-----------|---------------------------------|
| `min_row` | topmost row containing a `1`    |
| `max_row` | bottommost row containing a `1` |
| `min_col` | leftmost column containing a `1`|
| `max_col` | rightmost column containing a `1`|

**Complexity:**
- **Time:** $O(m \times n)$ — every cell is visited once.
- **Space:** $O(1)$ — only four integer variables are kept.

---

## Optimization

The current solution is already optimal in time ($O(m \times n)$) since every cell must be inspected at least once in the worst case. However, there are two practical improvements worth noting:

### 1. Early-termination row scan

Once we have found at least one `1`, the row scan for `min_row` can stop. Similarly, scanning rows from the bottom lets us stop early for `max_row`. The column boundaries can be derived from a single combined pass:

```python
class Solution:
    def minimumArea(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        # Find min_row: first row that contains a 1
        min_row = next(r for r in range(m)     if any(grid[r]))
        # Find max_row: last row that contains a 1
        max_row = next(r for r in range(m-1,-1,-1) if any(grid[r]))

        # Within the valid row band, find min_col and max_col
        min_col = n
        max_col = -1
        for r in range(min_row, max_row + 1):
            for c in range(n):
                if grid[r][c] == 1:
                    min_col = min(min_col, c)
                    max_col = max(max_col, c)

        return (max_row - min_row + 1) * (max_col - min_col + 1)
```

This skips rows outside `[min_row, max_row]` entirely for the column scan.

### 2. Numpy vectorized approach (Python-specific)

For large grids in Python, `numpy` can replace the nested loop with a highly optimized C-level operation:

```python
import numpy as np

class Solution:
    def minimumArea(self, grid: List[List[int]]) -> int:
        g = np.array(grid, dtype=bool)
        rows = np.any(g, axis=1).nonzero()[0]
        cols = np.any(g, axis=0).nonzero()[0]
        return int((rows[-1] - rows[0] + 1) * (cols[-1] - cols[0] + 1))
```

Same $O(m \times n)$ complexity but the constant factor is much smaller due to vectorisation.

### Summary

| Approach            | Time           | Space  | Notes                              |
|---------------------|----------------|--------|------------------------------------|
| Single nested loop  | $O(m \times n)$| $O(1)$ | Simple, always correct             |
| Early-termination   | $O(m \times n)$| $O(1)$ | Skips empty rows outside the band  |
| Numpy vectorized    | $O(m \times n)$| $O(m+n)$| Fastest in practice for Python    |

The single nested loop is already the theoretically optimal algorithm; the optimizations above reduce constant factors, not asymptotic complexity.
