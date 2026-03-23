## Problem

https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/description/

```
You are given a m x n matrix grid. Initially, you are located at the top-left 
corner (0, 0), and in each step, you can only move right or down in the matrix.

Among all possible paths starting from the top-left corner (0, 0) and ending 
in the bottom-right corner (m - 1, n - 1), find the path with the maximum 
non-negative product. The product of a path is the product of all integers 
in the grid cells visited along the path.

Return the maximum non-negative product modulo 10^9 + 7. If the maximum 
product is negative, return -1.

Constraints:
- m == grid.length
- n == grid[i].length
- 1 <= m, n <= 15
- -4 <= grid[i][j] <= 4
```

## Observations

1. **Dynamic Programming Problem**: Similar to minimum/maximum path sum, but with products instead of sums.

2. **Track Both Max AND Min**: This is crucial! When multiplying by negative numbers, the maximum can become minimum and vice versa. For example:
   - If current max is 8 and we multiply by -2, we get -16 (now it's the minimum)
   - If current min is -10 and we multiply by -2, we get 20 (now it's the maximum)

3. **Movement Constraints**: Can only move right or down, so each cell can only be reached from:
   - The cell above (i-1, j)
   - The cell to the left (i, j-1)

4. **Edge Cases**:
   - First row: can only come from left
   - First column: can only come from above
   - Zero in the grid: product becomes 0, which could be the best non-negative result

5. **Four Candidates per Cell**: For any cell (i, j) with value `val`, we have 4 products to consider:
   - `max_prod[i-1][j] * val` (from above, using max)
   - `max_prod[i][j-1] * val` (from left, using max)
   - `min_prod[i-1][j] * val` (from above, using min - could become max if val is negative)
   - `min_prod[i][j-1] * val` (from left, using min - could become max if val is negative)

## Solution

**Algorithm**: 2D Dynamic Programming with Max and Min Tracking

### Approach

1. **Initialize two DP tables**:
   - `max_prod[i][j]`: maximum product achievable at cell (i, j)
   - `min_prod[i][j]`: minimum product achievable at cell (i, j)
   - Both start with `grid[0][0]` at position (0, 0)

2. **Fill first column**: Only one path (straight down)
   ```python
   max_prod[r][0] = max_prod[r-1][0] * grid[r][0]
   min_prod[r][0] = max_prod[r][0]
   ```

3. **Fill first row**: Only one path (straight right)
   ```python
   max_prod[0][c] = max_prod[0][c-1] * grid[0][c]
   min_prod[0][c] = max_prod[0][c]
   ```

4. **Fill remaining cells**: Consider all 4 candidates
   ```python
   candidates = [
       max_prod[i-1][j] * val,  # from above, using previous max
       max_prod[i][j-1] * val,  # from left, using previous max
       min_prod[i-1][j] * val,  # from above, using previous min
       min_prod[i][j-1] * val   # from left, using previous min
   ]
   max_prod[i][j] = max(candidates)
   min_prod[i][j] = min(candidates)
   ```

5. **Return result**: 
   - If `max_prod[m-1][n-1] >= 0`, return it modulo 10^9 + 7
   - Otherwise, return -1

### Complexity Analysis

- **Time Complexity**: O(m × n) - visit each cell once
- **Space Complexity**: O(m × n) - two DP tables of size m × n

### Example Walkthrough

For `grid = [[1,-2,1],[1,-2,1],[3,-4,1]]`:

```
Step-by-step max_prod table:
[1,  -2,  -2]
[1,  -2,  -2]
[3, -12,   8]

Step-by-step min_prod table:
[1,  -2,  -2]
[1,  -2,  -2]
[3, -12,   8]
```

At (2, 2): candidates = [(-2) * 1, 8 * 1, (-2) * 1, (-12) * 1] = [-2, 8, -2, -12]
- max = 8
- Result: 8 % (10^9 + 7) = 8

# Tags
`Dynamic Programming`, `Matrix`, `Path Finding`, `Max/Min Tracking`

