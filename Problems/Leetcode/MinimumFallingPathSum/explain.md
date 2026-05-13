## Problem

https://leetcode.com/problems/minimum-falling-path-sum/description/

Given an **n × n** array of integers `matrix`, return the **minimum sum** of any falling path through the matrix.

A **falling path** starts at any element in the first row and chooses the element in the next row that is:
- Directly below: `(row + 1, col)`
- Diagonally left: `(row + 1, col - 1)`
- Diagonally right: `(row + 1, col + 1)`

### Examples

**Example 1:**
```
Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
Output: 13
Explanation: 
Path: 1 → 5 → 7 = 13 (or 1 → 4 → 8 = 13)
```

**Example 2:**
```
Input: matrix = [[-19,57],[-40,-5]]
Output: -59
Explanation: 
Path: 57 → -40 = -59 (starting from row 0, col 1, going to row 1, col 0)
```

### Constraints
- `n == matrix.length == matrix[i].length`
- `1 <= n <= 100`
- `-100 <= matrix[i][j] <= 100`

## Observations

1. **Optimal Substructure**: The minimum falling path sum ending at position `(r, c)` depends on the minimum path sums ending at valid positions in the next row: `(r+1, c-1)`, `(r+1, c)`, `(r+1, c+1)`.

2. **Bottom-up Computation**: It's natural to compute from the **last row upward** because:
   - Base case: Last row values are already known
   - Each cell in upper rows depends only on values already computed below it

3. **Boundary Handling**: For positions at the left/right edges:
   - Position `(r, c-1)` when `c=0` is invalid (out of bounds)
   - Position `(r, c+1)` when `c=n-1` is invalid (out of bounds)
   - We handle this by checking bounds or using padding with `infinity` values

4. **Two Approaches**:
   - **Top-down Memoization**: Start from row 0, recursively go down, cache results
   - **Bottom-up DP**: Fill DP table from last row to first row iteratively

5. **Space Optimization**: Can use 1D DP array since each row only depends on the next row, but 2D is clearer.

## Solution

### Approach 1: Top-down Memoization (Recursive)

```python
class Solution:
    def minFallingPathSum(self, grid: List[List[int]]) -> int:
        n = len(grid)
        mem = {}
        
        def F(r: int, c: int) -> int:
            # Out of bounds returns infinity
            if c < 0 or c >= n:
                return float('inf')
            
            # Base case: last row
            if r == n - 1:
                return grid[r][c]
            
            # Memoization check
            if (r, c) in mem:
                return mem[(r, c)]
            
            # Current cell + minimum of three choices below
            res = grid[r][c] + min(
                F(r + 1, c - 1),  # diagonal left
                F(r + 1, c),      # straight down
                F(r + 1, c + 1)   # diagonal right
            )
            
            mem[(r, c)] = res
            return res
        
        # Try all starting positions in first row
        res = float('inf')
        for i in range(n):
            res = min(res, F(0, i))
        return res
```

**Time Complexity**: O(n²) - Each of n² cells computed once  
**Space Complexity**: O(n²) - Memoization dictionary + recursion stack O(n)

---

### Approach 2: Bottom-up DP with Padding (Optimal)

```python
class Solution:
    def minFallingPathSum(self, grid: List[List[int]]) -> int:
        n = len(grid)
        
        # Create DP table with padding (n+2) columns
        # Padding: indices 0 and n+1 represent out-of-bounds areas with infinity
        dp = [[float('inf') for _ in range(n + 2)] for _ in range(n)]
        
        # Initialize last row (1-indexed due to padding)
        for i in range(n):
            dp[n - 1][i + 1] = grid[n - 1][i]
        
        # Fill DP table from second-to-last row to first row
        for r in range(n - 2, -1, -1):
            for c in range(1, n + 1):  # Use 1-indexed (padded indexing)
                # grid[r][c-1] because grid is 0-indexed
                # dp[r+1][c-1], dp[r+1][c], dp[r+1][c+1] are padded indices
                dp[r][c] = grid[r][c - 1] + min(
                    dp[r + 1][c - 1],  # from bottom-left
                    dp[r + 1][c],      # from bottom
                    dp[r + 1][c + 1]   # from bottom-right
                )
        
        # Find minimum in first row (1-indexed)
        res = float('inf')
        for i in range(1, n + 1):
            res = min(res, dp[0][i])
        return res
```

**Time Complexity**: O(n²) - Two nested loops over n² cells  
**Space Complexity**: O(n²) - DP table of size n × (n+2)

---

### Key Insights

1. **Padding Trick**: By creating `n+2` columns with padded boundaries set to `infinity`, we avoid explicit bound checking. Columns 0 and n+1 act as guards.

2. **Index Mapping**: Grid uses 0-based indexing `[0, n-1]`, while DP uses 1-based indexing `[1, n]` to accommodate padding.

3. **Why Bottom-up Works Better Here**: 
   - No recursion overhead
   - Natural iteration order (dependencies computed first)
   - Cleaner code without max recursion depth concerns

4. **Example Walkthrough** (matrix = `[[2,1,3],[6,5,4],[7,8,9]]`):
   ```
   Initial DP (last row):
   dp[2] = [inf, 7, 8, 9, inf]
   
   Compute row 1:
   dp[1][1] = 6 + min(inf, 7, 8) = 6 + 7 = 13
   dp[1][2] = 5 + min(7, 8, 9) = 5 + 7 = 12
   dp[1][3] = 4 + min(8, 9, inf) = 4 + 8 = 12
   dp[1] = [inf, 13, 12, 12, inf]
   
   Compute row 0:
   dp[0][1] = 2 + min(inf, 13, 12) = 2 + 12 = 14
   dp[0][2] = 1 + min(13, 12, 12) = 1 + 12 = 13
   dp[0][3] = 3 + min(12, 12, inf) = 3 + 12 = 15
   dp[0] = [inf, 14, 13, 15, inf]
   
   Result: min(14, 13, 15) = 13 ✓
   ```

# Tags
Dynamic Programming, Grid/Matrix, Memoization, Bottom-up DP, Optimal Path

