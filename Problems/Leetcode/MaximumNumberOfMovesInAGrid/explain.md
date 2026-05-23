## Problem

**LeetCode 2684: Maximum Number of Moves in a Grid**

https://leetcode.com/problems/maximum-number-of-moves-in-a-grid/description/

You are given a **0-indexed** `m x n` matrix `grid` consisting of **positive** integers.

You can start at **any** cell in the first column of the matrix, and traverse the grid in the following way:

- From a cell `(row, col)`, you can move to any of the cells: `(row - 1, col + 1)`, `(row, col + 1)` and `(row + 1, col + 1)` such that the value of the cell you move to, should be **strictly** bigger than the value of the current cell.

Return the **maximum** number of **moves** that you can perform.

**Constraints:**
- `m == grid.length`
- `n == grid[i].length`
- `2 <= m, n <= 1000`
- `1 <= grid[i][j] <= 10^6`

**Example 1:**
```
Input: grid = [[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]
Output: 3
Explanation: We can start at the cell (0, 0) and make the following moves:
- (0, 0) -> (0, 1): 2 -> 4
- (0, 1) -> (1, 2): 4 -> 9
- (1, 2) -> (2, 3): 9 -> 11
It can be shown that it is the maximum number of moves that can be made.
```

**Example 2:**
```
Input: grid = [[3,2,4],[2,1,9],[1,1,7]]
Output: 0
Explanation: Starting from any cell in the first column we cannot perform any moves.
```

## Observations

1. **Direction constraint**: We can only move right or diagonally right (col always increases by 1), which means:
   - Column moves strictly increase from `col` to `col + 1`
   - This guarantees we won't revisit cells since we always move to the next column
   - We can traverse at most `n - 1` moves (from column 0 to column n-1)

2. **Value constraint**: We must move to a strictly larger value, creating a strictly increasing path.

3. **Multiple starting points**: We must try all possible starting positions in the first column and take the maximum.

4. **Optimal substructure**: The maximum moves from cell `(r, c)` is 1 plus the maximum moves from the best next cell. This exhibits the optimal substructure property of dynamic programming.

5. **No cycles**: Since:
   - Column always increases
   - Values must strictly increase
   - There cannot be any cycles, making DFS + memoization safe

## Solution

**Approach: DFS with Memoization (Top-down Dynamic Programming)**

```python
class Solution:
    def maxMoves(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        mem = {}
        
        def F(r: int, c: int) -> int:
            # Base case: out of bounds or no valid moves possible
            if r < 0 or r >= m or c < 0 or c >= n:
                return 0
            
            # Return memoized result if already computed
            if (r, c) in mem:
                return mem[(r, c)]
            
            # Try all three possible moves: diagonal-up-right, right, diagonal-down-right
            res = 0
            for nr, nc in [(r - 1, c + 1), (r, c + 1), (r + 1, c + 1)]:
                # Check bounds
                if nr >= 0 and nr < m and nc >= 0 and nc < n:
                    # Only move if next cell has strictly larger value
                    if grid[r][c] < grid[nr][nc]:
                        # Take the maximum path: 1 move + best path from next cell
                        res = max(res, 1 + F(nr, nc))
            
            # Store result in memo
            mem[(r, c)] = res
            return res
        
        # Try starting from each row in the first column
        res = 0
        for r in range(m):
            res = max(res, F(r, 0))
        
        return res
```

**How it works:**

1. **Memoization**: `mem` dictionary stores the maximum moves achievable from each cell `(r, c)` to avoid recomputation.

2. **Recursive function F(r, c)**: Returns the maximum number of moves starting from cell `(r, c)`.
   - Base cases: If out of bounds, return 0 (no more moves possible).
   - Check memo: If already computed, return cached result.
   - Explore all three directions: For each of the three possible moves (diagonal up-right, straight right, diagonal down-right):
     - If the next cell is in bounds and has a strictly larger value, recursively compute the maximum moves from that cell.
     - Track the best option.
   - Memoize and return the result.

3. **Main logic**: Try starting from each row in column 0, and return the maximum number of moves across all starting positions.

**Time Complexity**: $O(m \times n)$
- Each cell is computed at most once due to memoization
- For each cell, we check 3 possible moves: $O(1)$

**Space Complexity**: $O(m \times n)$
- Memoization table stores results for each cell
- Recursion stack depth is at most $n$ (move at most `n-1` steps to the right)

# Tags

