## Problem

https://leetcode.com/problems/subrectangle-queries/description/

Design a class `SubrectangleQueries` that wraps a 2D integer matrix and supports two operations:

1. **`updateSubrectangle(row1, col1, row2, col2, newValue)`** — Set every cell inside the subrectangle defined by its upper-left corner `(row1, col1)` and bottom-right corner `(row2, col2)` to `newValue`.
2. **`getValue(row, col)`** — Return the current value at cell `(row, col)`.

**Constraints:**
- At most **500** total operations.
- Matrix dimensions: `1 ≤ rows, cols ≤ 100`.
- Cell values and `newValue`: `1 ≤ value ≤ 10⁹`.

---

## Observations

1. **Naïve update is affordable** — With at most 500 operations and a grid of at most 100×100 = 10 000 cells, even updating every cell in the rectangle on every `updateSubrectangle` call would be at most 500 × 10 000 = 5 000 000 operations — well within limits.

2. **Lazy / patch approach is even simpler** — Instead of physically writing `newValue` into the grid, we can *record* each update as a patch `(r1, c1, r2, c2, val)` in a list. When `getValue(r, c)` is called, we **scan the patch list in reverse order** (most-recent first). The first patch that contains `(r, c)` wins. If no patch covers the cell, we fall back to the original grid value.

3. **Why reverse order?** Later updates overwrite earlier ones for the same cells. Scanning newest-to-oldest naturally implements this "last writer wins" semantics without ever modifying the recorded patches.

4. **Time complexity:**
   - `updateSubrectangle`: O(1) — just append a tuple.
   - `getValue`: O(P) where P is the number of patches recorded so far (at most 500).

5. **Space complexity:** O(P) extra for the patch list, plus O(rows × cols) for the original grid.

---

## Solution

```python
class SubrectangleQueries:

    def __init__(self, rectangle: List[List[int]]):
        # Store the original grid unchanged.
        self.grid = rectangle
        # Each entry is (r1, c1, r2, c2, value) representing a rectangle update.
        self.patches = []

    def updateSubrectangle(self, r: int, c: int, nr: int, nc: int, val: int) -> None:
        # Record the update lazily — O(1).
        self.patches.append((r, c, nr, nc, val))

    def getValue(self, r: int, c: int) -> int:
        # Walk patches from newest to oldest.
        # Return the value of the first (most-recent) patch that covers (r, c).
        for pr1, pc1, pr2, pc2, val in reversed(self.patches):
            if pr1 <= r <= pr2 and pc1 <= c <= pc2:
                return val

        # No patch covers this cell — return the original grid value.
        return self.grid[r][c]


# Your SubrectangleQueries object will be instantiated and called as such:
# obj = SubrectangleQueries(rectangle)
# obj.updateSubrectangle(row1, col1, row2, col2, newValue)
# param_2 = obj.getValue(row, col)
```

### Step-by-step trace (Example 1)

| Call | patches list (newest last) | Returned |
|------|---------------------------|----------|
| `SubrectangleQueries([[1,2,1],[4,3,4],[3,2,1],[1,1,1]])` | `[]` | — |
| `getValue(0, 2)` | no patch covers (0,2) → grid[0][2] | **1** |
| `updateSubrectangle(0,0,3,2,5)` | `[(0,0,3,2,5)]` | — |
| `getValue(0, 2)` | patch (0,0,3,2,5) covers (0,2) | **5** |
| `getValue(3, 1)` | patch (0,0,3,2,5) covers (3,1) | **5** |
| `updateSubrectangle(3,0,3,2,10)` | `[(0,0,3,2,5),(3,0,3,2,10)]` | — |
| `getValue(3, 1)` | newest patch (3,0,3,2,10) covers (3,1) | **10** |
| `getValue(0, 2)` | newest patch (3,0,3,2,10) does **not** cover (0,2); older patch (0,0,3,2,5) does | **5** |
