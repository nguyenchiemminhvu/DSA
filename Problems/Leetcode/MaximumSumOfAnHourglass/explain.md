## Problem

https://leetcode.com/problems/maximum-sum-of-an-hourglass/description/

You are given an `m x n` integer matrix `grid`.

An **hourglass** is a fixed shape in the matrix:
```
a b c
  d
e f g
```
That is: 3 cells in the top row, 1 cell in the middle (centered), and 3 cells in the bottom row — 7 cells total.

Return the **maximum sum** of the elements of any hourglass. The hourglass cannot be rotated and must be entirely within the matrix.

**Constraints:**
- `m == grid.length`
- `n == grid[i].length`
- `3 <= m, n <= 150`
- `0 <= grid[i][j] <= 10^6`

**Examples:**

Example 1:
```
Input: grid = [[6,2,1,3],[4,2,1,5],[9,2,8,7],[4,1,2,9]]
Output: 30
Explanation: 6 + 2 + 1 + 2 + 9 + 2 + 8 = 30
```

Example 2:
```
Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
Output: 35
Explanation: Only one hourglass: 1 + 2 + 3 + 5 + 7 + 8 + 9 = 35
```

## Observations

1. **Hourglass structure:** An hourglass centered at `(i, j)` (where `j` is the middle column) spans:
   - Top row: `grid[i-1][j-1]`, `grid[i-1][j]`, `grid[i-1][j+1]`
   - Middle: `grid[i][j]`
   - Bottom row: `grid[i+1][j-1]`, `grid[i+1][j]`, `grid[i+1][j+1]`
   
   Equivalently, we can think of the **top-left corner** at `(r, c)`, where the hourglass occupies rows `r, r+1, r+2` and columns `c, c+1, c+2`.

2. **Valid positions:** The top-left corner `(r, c)` is valid when:
   - `0 <= r <= m - 3`
   - `0 <= c <= n - 3`
   
   So there are `(m-2) * (n-2)` possible hourglasses.

3. **Brute Force (Direct Simulation):** For each valid top-left corner `(r, c)`, compute the hourglass sum directly:
   ```
   sum = grid[r][c] + grid[r][c+1] + grid[r][c+2]
       +               grid[r+1][c+1]
       + grid[r+2][c] + grid[r+2][c+1] + grid[r+2][c+2]
   ```
   Track the maximum. Time: O(m * n), Space: O(1).

4. **Can we use prefix sums?** Each hourglass sum can be expressed as: sum of the full 3x3 block minus the left and right cells of the middle row. A 2D prefix sum array allows each 3×3 block sum to be computed in O(1), reducing repeated work. However, since each hourglass already requires O(1) computation with direct access, prefix sums are an over-engineering here — direct simulation is optimal.

5. **Key constraints note:** All values are non-negative (`0 <= grid[i][j] <= 10^6`), so the maximum sum is always well-defined and at least 0. We can safely initialize `max_sum = 0` or `float('-inf')`.

## Solution

**Approach: Brute Force — Enumerate All Valid Hourglasses**

```python
class Solution:
    def maxSum(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        max_sum = 0

        for r in range(m - 2):
            for c in range(n - 2):
                hourglass_sum = (
                    grid[r][c]   + grid[r][c+1]   + grid[r][c+2] +
                                   grid[r+1][c+1] +
                    grid[r+2][c] + grid[r+2][c+1] + grid[r+2][c+2]
                )
                max_sum = max(max_sum, hourglass_sum)

        return max_sum
```

**Complexity:**
- Time: O(m × n) — each cell is visited at most a constant number of times
- Space: O(1) — no extra data structures

**Walk-through (Example 1):**
```
grid = [[6,2,1,3],
        [4,2,1,5],
        [9,2,8,7],
        [4,1,2,9]]

(r=0, c=0): 6+2+1 + 2 + 9+2+8 = 30  ← max
(r=0, c=1): 2+1+3 + 1 + 2+8+7 = 24
(r=1, c=0): 4+2+1 + 2 + 4+1+2 = 16
(r=1, c=1): 2+1+5 + 8 + 1+2+9 = 28

Answer: 30
```

# Tags

- Array
- Matrix
- Prefix Sum
