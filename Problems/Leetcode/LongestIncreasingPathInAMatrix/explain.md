## Problem

https://leetcode.com/problems/longest-increasing-path-in-a-matrix/description

Given an m x n integers matrix, return the length of the longest increasing path in the matrix.

From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).

**Examples:**

**Example 1:**
- Input: `matrix = [[9,9,4],[6,6,8],[2,1,1]]`
- Output: `4`
- Explanation: The longest increasing path is `[1, 2, 6, 9]`

**Example 2:**
- Input: `matrix = [[3,4,5],[3,2,6],[2,2,1]]`
- Output: `4`
- Explanation: The longest increasing path is `[3, 4, 5, 6]`

**Example 3:**
- Input: `matrix = [[1]]`
- Output: `1`

**Constraints:**
- m == matrix.length
- n == matrix[i].length
- 1 <= m, n <= 200
- 0 <= matrix[i][j] <= 2^31 - 1

## Observations

1. **Key Insight**: An increasing path can only go from a smaller value to a larger value. This means if we process cells in sorted order (from smallest to largest), we can build up the longest path incrementally.

2. **Directional Flow**: From any cell, we can move in 4 directions (up, down, left, right). We need to check if the next cell has a larger value - only then can we extend the path.

3. **Two Approaches**:
   - **DFS with Memoization** (Top-Down): Start from each cell, explore all possible increasing paths, memoize results
   - **Dynamic Programming** (Bottom-Up): Sort cells by value, process from smallest to largest, use DP to track longest path ending at each cell

4. **Why Bottom-Up DP Works**: 
   - By sorting cells, when we process cell with value `v`, all cells with smaller values have already been processed
   - If we find a neighbor with a larger value, we can update its longest path to `max(neighbor_dp, current_dp + 1)`
   - This avoids revisiting the same cell multiple times

5. **Time Complexity Analysis**:
   - Sorting: O(m·n·log(m·n))
   - Processing: O(m·n·4) = O(m·n) (each cell checked with 4 neighbors)
   - Total: O(m·n·log(m·n))

## Solution

```python
class Solution:
    def longestIncreasingPath(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        
        # Create list of (value, row, col) and sort by value
        cells = [(grid[r][c], r, c) for r in range(m) for c in range(n)]
        cells.sort(key=lambda x: x[0])
        
        # dp[r][c] = longest increasing path starting from (r, c)
        dp = [[1] * n for _ in range(m)]
        
        # Process cells from smallest to largest value
        for i in range(len(cells)):
            val, r, c = cells[i]
            # Check all 4 neighbors
            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                if 0 <= nr < m and 0 <= nc < n:
                    # If neighbor has larger value, we can extend the path
                    if val < grid[nr][nc]:
                        dp[nr][nc] = max(dp[nr][nc], 1 + dp[r][c])
        
        # Return the maximum value in the dp table
        return max(max(row) for row in dp)
```

### Alternative Approach: DFS with Memoization

```python
class Solution:
    def longestIncreasingPath(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        mem = {}
        
        def dfs(r: int, c: int) -> int:
            # Out of bounds returns 0
            if r < 0 or r >= m or c < 0 or c >= n:
                return 0
            
            # Return memoized result if exists
            if (r, c) in mem:
                return mem[(r, c)]
            
            # Base case: path of length 1
            res = 1
            
            # Explore all 4 directions
            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                if 0 <= nr < m and 0 <= nc < n:
                    # Only extend path if next cell is smaller
                    if grid[nr][nc] < grid[r][c]:
                        res = max(res, 1 + dfs(nr, nc))
            
            mem[(r, c)] = res
            return res
        
        # Try starting from each cell and find the maximum
        res = 0
        for r in range(m):
            for c in range(n):
                res = max(res, dfs(r, c))
        return res
```

## Key Differences Between Approaches

| Aspect | DFS + Memo | DP (Sorted) |
|--------|-----------|-----------|
| **Direction** | Top-Down (from larger to smaller) | Bottom-Up (from smaller to larger) |
| **Starting Point** | Every cell is tried as starting point | Built incrementally |
| **Space** | Memoization dictionary + recursion stack | 2D DP array |
| **Intuition** | "What's the longest path FROM this cell?" | "What's the longest path TO larger neighbors?" |
| **Better for** | Sparse matrices where not all paths explored | Dense matrices, iterative preference |

## Solution Complexity

**Bottom-Up DP Approach:**
- **Time:** O(m·n·log(m·n)) - Sorting dominates
- **Space:** O(m·n) - DP table

**DFS + Memoization Approach:**
- **Time:** O(m·n) - Each cell visited once due to memoization
- **Space:** O(m·n) - Memoization + O(m·n) recursion depth in worst case

## Example Walkthrough (DP Approach)

Given: `matrix = [[9,9,4],[6,6,8],[2,1,1]]`

**Step 1: Sort cells by value**
- Cells: `[(1,2,1), (1,2,2), (2,2,0), (4,0,2), (6,1,0), (6,1,1), (8,1,2), (9,0,0), (9,0,1)]`

**Step 2: Process in sorted order**
- Start: `dp = [[1,1,1],[1,1,1],[1,1,1]]`
- Process (1, 2,1): neighbors [1, 2, 6, 1] → no larger processed yet
- Process (1, 2,2): neighbors [1, 8] → no larger processed yet
- Process (2, 2,0): neighbors [1, 6] → update dp[1][0] = max(1, 1+1) = 2
- Process (4, 0,2): neighbors [9, 8] → update dp[1][2] = max(1, 1+1) = 2
- Process (6, 1,0): neighbors [2, 9, 6] → update dp[0][0] = max(1, 1+2) = 3
- Process (6, 1,1): neighbors [9, 4, 6, 1] → update dp[0][1] = max(1, 1+1) = 2
- Process (8, 1,2): neighbors [4, 6, 9] → dp[0][2] already max'd
- Process (9, 0,0) and (9, 0,1): neighbors checked
- **Result:** max(dp) = 4 ✓

# Tags
- Dynamic Programming
- Depth-First Search
- Memoization
- Matrix
- Topological Sort
- Sorting

