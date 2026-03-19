## Problem

https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/description/

Given a 2D character matrix `grid`, where `grid[i][j]` is either `'X'`, `'Y'`, or `'.'`, return the number of submatrices that satisfy **all** of the following conditions:

1. The submatrix contains `grid[0][0]` (i.e., it always starts at the top-left corner).
2. It has an **equal** frequency of `'X'` and `'Y'`.
3. It contains **at least one** `'X'`.

**Constraints:**
- `1 <= grid.length, grid[i].length <= 1000`
- `grid[i][j]` is either `'X'`, `'Y'`, or `'.'`

**Examples:**

```
Input: grid = [["X","Y","."],["Y",".","."]]
Output: 3

Input: grid = [["X","X"],["X","Y"]]
Output: 0  (no submatrix has equal frequency of 'X' and 'Y')

Input: grid = [[".","."],[".","."]]
Output: 0  (no submatrix has at least one 'X')
```

## Observations

- Every valid submatrix **must start at `grid[0][0]`**, meaning we only consider submatrices of the form `grid[0..i][0..j]` (top-left anchored). This dramatically simplifies the problem — we don't need to enumerate all possible start points.

- Because all submatrices share the same top-left corner, we can use a **2D prefix sum** to efficiently compute the count of `'X'` and `'Y'` in any such submatrix in O(1).

- The prefix sum for a cell `(i, j)` is computed using the standard **inclusion-exclusion** formula:
  ```
  prefix[i][j] = cell[i][j] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1]
  ```
  Since the submatrix always starts at `(0, 0)`, `prefix[i][j]` directly gives the total count of `'X'` (or `'Y'`) in the rectangle from `(0,0)` to `(i,j)`.

- After building the prefix sums, checking each submatrix `(0,0)→(i,j)` is just a matter of comparing `prefixX[i][j] == prefixY[i][j]` and `prefixX[i][j] > 0`.

- Time complexity: **O(m × n)** — one pass to build prefix sums, one pass to count valid submatrices.
- Space complexity: **O(m × n)** — the prefix sum matrix.

## Solution

We maintain a 2D prefix sum matrix where each cell stores two values: the cumulative count of `'X'` and `'Y'` from `(0, 0)` to `(i, j)`.

**Step 1 — Build the prefix sum matrix:**

Initialize `mat[i][j]` as `[1, 0]` if `'X'`, `[0, 1]` if `'Y'`, or `[0, 0]` if `'.'`.  
Then apply the 2D prefix sum recurrence using inclusion-exclusion:

```
mat[i][j][0] += mat[i-1][j][0] + mat[i][j-1][0] - mat[i-1][j-1][0]
mat[i][j][1] += mat[i-1][j][1] + mat[i][j-1][1] - mat[i-1][j-1][1]
```

**Step 2 — Count valid submatrices:**

For each `(i, j)`, if `mat[i][j][0] > 0` (at least one `'X'`) and `mat[i][j][0] == mat[i][j][1]` (equal count of `'X'` and `'Y'`), increment the answer.

```python
class Solution:
    def numberOfSubmatrices(self, grid: List[List[str]]) -> int:
        m = len(grid)
        n = len(grid[0])

        mat = [[[1 if c == 'X' else 0, 1 if c == 'Y' else 0] for c in row] for row in grid]
        for i in range(m):
            for j in range(n):
                if i > 0:
                    mat[i][j][0] += mat[i-1][j][0]
                    mat[i][j][1] += mat[i-1][j][1]
                if j > 0:
                    mat[i][j][0] += mat[i][j-1][0]
                    mat[i][j][1] += mat[i][j-1][1]
                if i > 0 and j > 0:
                    mat[i][j][0] -= mat[i-1][j-1][0]
                    mat[i][j][1] -= mat[i-1][j-1][1]
        
        count = 0
        for i in range(m):
            for j in range(n):
                if mat[i][j][0] > 0 and mat[i][j][0] == mat[i][j][1]:
                    count += 1
        return count
```

# Tags

`2D Prefix Sum` `Matrix` `Counting`

