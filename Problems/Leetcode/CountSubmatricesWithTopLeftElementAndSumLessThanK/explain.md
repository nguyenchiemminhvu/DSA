## Problem

https://leetcode.com/problems/count-submatrices-with-top-left-element-and-sum-less-than-k/description/

````markdown
## Problem

https://leetcode.com/problems/count-submatrices-with-top-left-element-and-sum-less-than-k/description/

Given a 0-indexed integer matrix `grid` of size `m x n` and an integer `k`, return the **number of submatrices** that:
1. **Contain the top-left element** `grid[0][0]` (i.e., the submatrix starts at row 0, column 0), and
2. Have a **sum less than or equal to `k`**.

A submatrix anchored at the top-left is fully defined by its bottom-right corner `(i, j)`, spanning rows `[0..i]` and columns `[0..j]`.

**Examples:**
- `grid = [[7,6,3],[6,6,1]]`, `k = 18` → Output: `4`
- `grid = [[7,2,9],[1,5,0],[2,6,6]]`, `k = 20` → Output: `6`

**Constraints:**
- `1 <= m, n <= 1000`
- `0 <= grid[i][j] <= 1000`
- `1 <= k <= 10^9`

## Observations

1. **Submatrix shape**: Every valid submatrix must include `grid[0][0]`. This means a submatrix is uniquely identified by its bottom-right corner `(i, j)`. There are exactly `m × n` such submatrices to consider.

2. **Sum of a submatrix**: Computing the sum of each submatrix from scratch would be O(m²·n²) in the worst case — too slow for `m, n = 1000`. We need a smarter approach.

3. **2D Prefix Sum**: We can precompute a 2D prefix sum table where `prefix[i][j]` equals the sum of all elements in the submatrix from `(0,0)` to `(i,j)`. Using the inclusion-exclusion principle:

$$
\text{prefix}[i][j] = \text{grid}[i][j] + \text{prefix}[i-1][j] + \text{prefix}[i][j-1] - \text{prefix}[i-1][j-1]
$$

   After building this table in-place, `grid[i][j]` directly holds the sum of the submatrix `(0,0) → (i,j)`.

4. **Single pass counting**: Once the prefix sums are built, a single pass over all cells checking `grid[i][j] <= k` gives the answer in O(m·n).

## Solution

The solution builds the 2D prefix sum **in-place** on `grid`, then counts cells where the prefix sum ≤ k.

```python
class Solution:
    def countSubmatrices(self, grid: List[List[int]], k: int) -> int:
        m = len(grid)
        n = len(grid[0])

        # Build 2D prefix sum in-place using inclusion-exclusion
        for i in range(m):
            for j in range(n):
                if i > 0:
                    grid[i][j] += grid[i-1][j]   # add row above
                if j > 0:
                    grid[i][j] += grid[i][j-1]   # add column to the left
                if i > 0 and j > 0:
                    grid[i][j] -= grid[i-1][j-1] # subtract double-counted top-left rectangle

        # Count submatrices whose total sum <= k
        count = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] <= k:
                    count += 1
        return count
```

**Step-by-step walkthrough (Example 1: `grid = [[7,6,3],[6,6,1]]`, `k = 18`):**

| Step | (i,j) | Prefix sum computation | Value |
|------|-------|------------------------|-------|
| Init | (0,0) | 7 | 7 |
| Init | (0,1) | 7 + 6 = 13 | 13 |
| Init | (0,2) | 13 + 3 = 16 | 16 |
| Init | (1,0) | 7 + 6 = 13 | 13 |
| Init | (1,1) | 6 + 13 + 13 − 7 = 25 | 25 |
| Init | (1,2) | 1 + 25 + 16 − 13 = 29 | 29 |

Prefix grid: `[[7, 13, 16], [13, 25, 29]]`

Cells with value ≤ 18: `(0,0)=7`, `(0,1)=13`, `(0,2)=16`, `(1,0)=13` → **count = 4** ✓

**Complexity:**
- **Time:** O(m·n) — one pass to build prefix sums, one pass to count.
- **Space:** O(1) extra — prefix sums are built in-place on `grid`.

# Tags

`Array` `Matrix` `Prefix Sum`
````

## Observations

## Solution

# Tags

