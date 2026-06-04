## Problem

https://leetcode.com/problems/matrix-block-sum/description/

Given a `m x n` matrix `mat` and an integer `k`, return a matrix `answer` where each `answer[i][j]` is the sum of all elements `mat[r][c]` for:

- `i - k <= r <= i + k`
- `j - k <= c <= j + k`
- `(r, c)` is a valid position in the matrix (i.e., within bounds)

In other words, for every cell `(i, j)` in the result matrix, sum all elements of `mat` that lie within a `(2k+1) x (2k+1)` window centered at `(i, j)`, clamping to the matrix boundaries.

**Example 1:**
```
Input:  mat = [[1,2,3],[4,5,6],[7,8,9]], k = 1
Output: [[12,21,16],[27,45,33],[24,39,28]]
```

**Example 2:**
```
Input:  mat = [[1,2,3],[4,5,6],[7,8,9]], k = 2
Output: [[45,45,45],[45,45,45],[45,45,45]]
```

---

## Observations

1. **Brute force is too slow.** For each of the `m*n` cells, summing a `(2k+1)^2` window naively gives `O(m * n * k^2)` time. With `m, n, k` up to 100 that's 100 * 100 * 100^2 = 10^8, which is borderline — a smarter approach is preferred.

2. **2D Prefix Sum (cumulative sum) is the key insight.** If we precompute a 2D prefix sum array `P` where `P[r][c]` = sum of all elements in the sub-matrix from `(0,0)` to `(r,c)`, then the sum of any rectangular sub-matrix from `(r1,c1)` to `(r2,c2)` can be computed in **O(1)**:

$$\text{RectSum}(r1,c1,r2,c2) = P[r2][c2] - P[r1-1][c2] - P[r2][c1-1] + P[r1-1][c1-1]$$

   This is the **inclusion-exclusion** principle on overlapping prefix regions.

3. **Window clamping.** Since the window `[i-k, i+k] x [j-k, j+k]` may extend beyond the matrix, we clamp:
   - `r1 = max(0, i - k)`, `c1 = max(0, j - k)`
   - `r2 = min(m-1, i + k)`, `c2 = min(n-1, j + k)`

4. **Boundary guards** are needed when applying the inclusion-exclusion formula, because `r1-1` or `c1-1` may become `-1` (out of bounds). When that happens, the subtracted term is simply 0.

---

## Solution Explanation

### Step 1 — Build the 2D Prefix Sum

```
P[r][c] = mat[r][c]
        + P[r-1][c]      (row above)
        + P[r][c-1]      (column left)
        - P[r-1][c-1]    (subtract the overlap counted twice)
```

Visually, `P[r][c]` accumulates the total sum of the rectangle from the top-left corner `(0,0)` down to `(r,c)`.

```
mat:           prefix sum P:
1  2  3        1   3   6
4  5  6   →    5  12  21
7  8  9        12  27  45
```

### Step 2 — Query each window using O(1) rectangle sum

For each output cell `(i, j)`:

1. Clamp the window corners:
   - `(r1, c1) = (max(0, i-k), max(0, j-k))`
   - `(r2, c2) = (min(m-1, i+k), min(n-1, j+k))`

2. Apply the rectangle sum formula with boundary guards:

```
total = P[r2][c2]
      - (P[r1-1][c2]  if r1 > 0 else 0)
      - (P[r2][c1-1]  if c1 > 0 else 0)
      + (P[r1-1][c1-1] if r1 > 0 and c1 > 0 else 0)
```

This gives the block sum for `answer[i][j]` in O(1).

### Why the inclusion-exclusion works

```
  (0,0)──────────(0,c2)
    |        |        |
    |   A    |   B    |
    |        |        |
  (r1,0)────(r1,c1)──(r1,c2)
    |        |        |
    |   C    |  [D]   |
    |        |        |
  (r2,0)────(r2,c1)──(r2,c2)
```

- `P[r2][c2]` = A + B + C + D  
- `P[r1-1][c2]` = A + B  
- `P[r2][c1-1]` = A + C  
- `P[r1-1][c1-1]` = A  

So: `D = P[r2][c2] - (A+B) - (A+C) + A = P[r2][c2] - P[r1-1][c2] - P[r2][c1-1] + P[r1-1][c1-1]`

### Complexity

| | Time | Space |
|---|---|---|
| Build prefix sum | O(m × n) | O(m × n) |
| Query all cells | O(m × n) | O(1) per query |
| **Total** | **O(m × n)** | **O(m × n)** |

---

## Code

```python
class Solution:
    def matrixBlockSum(self, grid: List[List[int]], k: int) -> List[List[int]]:
        def cumsum(grid):
            if not grid or not grid[0]:
                return []
            m, n = len(grid), len(grid[0])
            cum_grid = [[0 for _ in range(n)] for _ in range(m)]
            for r in range(m):
                for c in range(n):
                    val = grid[r][c]
                    if r > 0:
                        val += cum_grid[r-1][c]
                    if c > 0:
                        val += cum_grid[r][c-1]
                    if r > 0 and c > 0:
                        val -= cum_grid[r-1][c-1]  # Subtract overlap
                    cum_grid[r][c] = val
            return cum_grid

        m, n = len(grid), len(grid[0])
        cum_grid = cumsum(grid)
        res = [[0] * n for _ in range(m)]
        for r in range(m):
            for c in range(n):
                r1 = max(0, r - k)
                c1 = max(0, c - k)
                r2 = min(m - 1, r + k)
                c2 = min(n - 1, c + k)
                total_sum = cum_grid[r2][c2]
                if r1 > 0:
                    total_sum -= cum_grid[r1 - 1][c2]
                if c1 > 0:
                    total_sum -= cum_grid[r2][c1 - 1]
                if r1 > 0 and c1 > 0:
                    total_sum += cum_grid[r1 - 1][c1 - 1]
                res[r][c] = total_sum
        return res
```
