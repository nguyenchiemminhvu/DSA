## Problem

https://leetcode.com/problems/out-of-boundary-paths/description

There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn]. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply at most maxMove moves to the ball.

**Task:** Return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it modulo 10^9 + 7.

**Examples:**

Example 1:
- Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
- Output: 6
- Explanation: The ball can move out of the grid in 6 different ways with at most 2 moves.

Example 2:
- Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
- Output: 12

**Constraints:**
- 1 <= m, n <= 50
- 0 <= maxMove <= 50
- 0 <= startRow < m
- 0 <= startColumn < n

## Observations

1. **Counting Paths:** This problem requires counting all distinct paths from the start position that result in the ball going out of bounds within maxMove moves.

2. **State Definition:** A state is defined by (row, column, moves_used). We need to track which cells we can reach with a certain number of moves.

3. **Base Cases:** 
   - If we go out of bounds (row < 0, row >= m, col < 0, col >= n), we've found a valid path.
   - If we've used all maxMove moves without going out of bounds, this path doesn't contribute to the answer.

4. **Four Directions:** From any cell, the ball can move in 4 directions: up, down, left, right.

5. **Overlapping Subproblems:** Many different paths may reach the same cell with the same number of moves. This suggests memoization or dynamic programming.

6. **Two Approaches:**
   - **Top-Down (Memoization):** Start from the beginning position and recursively explore all paths, caching results.
   - **Bottom-Up (Tabulation):** Process each "move level" iteratively, tracking how many ways we can reach each cell after k moves.

7. **Modulo Operation:** Since answers can be very large, apply modulo 10^9 + 7 at each addition to prevent overflow and keep numbers manageable.

## Solution

The provided solution uses a **bottom-up dynamic programming approach** with level-by-level processing:

### Key Insight
Instead of tracking which cells we've visited at each move count, we track **how many ways we can reach each cell** after exactly k moves. This is more efficient than recursion with memoization for this problem.

### Algorithm

1. **Initialize:** Create a DP table where `dp[r][c]` represents the number of ways to reach cell (r, c) from the start position. Initially, only `dp[start_r][start_c] = 1`.

2. **Process Each Move Level:** For k from 0 to maxMove-1:
   - Create a new DP table `new_dp` to store results for the next move level
   - For each cell (r, c) where `dp[r][c] > 0`:
     - Get `ways = dp[r][c]` (number of ways to reach this cell)
     - Try all 4 adjacent cells (up, down, left, right):
       - **If the adjacent cell is out of bounds:** This path found a solution, so add `ways` to the result
       - **If the adjacent cell is in bounds:** Add `ways` to `new_dp[nr][nc]` (accumulate ways to reach the next cell)
   - Update `dp = new_dp` for the next iteration

3. **Return:** The accumulated result modulo 10^9 + 7

### Why This Approach is Efficient

- **Space:** O(m × n) - we only need to store the current and next move levels
- **Time:** O(maxMove × m × n × 4) = O(maxMove × m × n) - process each cell for each move level
- **No Redundant Computation:** Unlike recursive memoization, this avoids recalculating the same subproblems from multiple paths

### Example Walkthrough (m=2, n=2, maxMove=2, start=(0,0))

**Move 0:** `dp = [[1, 0], [0, 0]]` (ball at (0,0))

**Move 1:**
- From (0,0), try (1,0), (-1,0), (0,1), (0,-1)
- (-1,0) and (0,-1) are out of bounds → res += 2
- (1,0) and (0,1) are in bounds → `new_dp = [[0, 1], [1, 0]]`

**Move 2:**
- From (1,0), try (2,0), (0,0), (1,1), (1,-1)
  - (2,0) and (1,-1) are out of bounds → res += 2
  - (0,0) and (1,1) are in bounds → `new_dp[0][0] += 1`, `new_dp[1][1] += 1`
- From (0,1), try (1,1), (-1,1), (0,2), (0,0)
  - (-1,1) and (0,2) are out of bounds → res += 2
  - (1,1) and (0,0) are in bounds

**Final result:** 6

# Tags

Dynamic Programming, Memoization, Grid, Combinatorics

