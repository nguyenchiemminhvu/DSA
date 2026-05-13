## Problem

https://leetcode.com/problems/minimum-path-sum/description

Given an **m x n grid** filled with non-negative numbers, find a path from **top-left to bottom-right** that minimizes the sum of all numbers along the path.

**Constraints:**
- You can only move **down** or **right** at any point in time
- m == grid.length
- n == grid[i].length  
- 1 <= m, n <= 200
- 0 <= grid[i][j] <= 200

**Example 1:**
```
Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7
Explanation: Path 1 → 3 → 1 → 1 → 1 minimizes the sum
```

**Example 2:**
```
Input: grid = [[1,2,3],[4,5,6]]
Output: 12
```

## Observations

1. **Path Constraint:** Since we can only move right or down, there's a unique structure to how we can reach any cell (i, j) - we must come from either the cell above (i-1, j) or the cell to the left (i, j-1).

2. **Optimal Substructure:** The minimum path sum to reach cell (i, j) depends on the minimum path sums to reach (i-1, j) and (i, j-1), which is characteristic of dynamic programming problems.

3. **No Backtracking:** The constraint of only moving right/down means we can't backtrack or explore complex paths - this simplifies the problem significantly compared to graphs with arbitrary edges.

4. **Boundary Conditions:** 
   - Top-left cell (0, 0) can only be reached via itself: min_sum[0][0] = grid[0][0]
   - First row cells can only be reached from the left
   - First column cells can only be reached from above

5. **Overlapping Subproblems:** If we were to use recursion, many cells would be computed multiple times (e.g., reaching (2,2) involves computing (1,2) and (2,1), both of which eventually need (1,1)).

## Solution

### Approach: Dynamic Programming (Bottom-Up - Tabulation)

**Time Complexity:** O(m × n)  
**Space Complexity:** O(m × n) for the DP table

**Key Insight:** Build a 2D DP table where `dp[i][j]` represents the minimum sum needed to reach cell (i, j) from (0, 0).

**Algorithm:**

1. **Initialize:** Create a DP table of size m × n
2. **Base Case:** Set dp[0][0] = grid[0][0]
3. **Fill First Row:** Each cell can only come from the left
   - `dp[0][i] = dp[0][i-1] + grid[0][i]`
4. **Fill First Column:** Each cell can only come from above
   - `dp[i][0] = dp[i-1][0] + grid[i][0]`
5. **Fill Remaining Cells:** For each cell (i, j), take the minimum of coming from above or left
   - `dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])`
6. **Return:** dp[m-1][n-1] contains the answer

**Why This Works:**
- We ensure that when we compute dp[i][j], we've already computed all cells it depends on (dp[i-1][j] and dp[i][j-1])
- The recurrence relation directly translates the constraint: we can only arrive from above or left
- Building bottom-up avoids recursion overhead and memoization lookup costs

**Example Walkthrough:**
```
Grid:                  DP Table:
[1, 3, 1]              [1,  4,  5]
[1, 5, 1]              [2,  7,  6]
[4, 2, 1]              [6,  8,  7]
```

For dp[1][1] = 7: min_sum to (1,1) is 1 (start) + 1 (down) + 5 (right) OR 1 + 3 (right) + 5 (down) = 7

### Alternative Approach: Recursion with Memoization (Top-Down)

The commented code shows a memoized recursive solution:
- **Time Complexity:** O(m × n)
- **Space Complexity:** O(m × n) for memoization + O(m + n) for recursion stack
- **When to use:** When you need to only compute reachable subproblems or prefer top-down thinking

The key difference is:
- Start from destination (m-1, n-1) and work backwards to (0, 0)
- Use a memo dictionary to cache results
- Handle boundary cases (negative indices) by returning infinity for invalid positions

# Tags

- Dynamic Programming
- Grid Path
- Bottom-Up Tabulation
- Optimal Substructure

