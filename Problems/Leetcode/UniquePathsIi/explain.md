## Problem

https://leetcode.com/problems/unique-paths-ii/description

## Problem

https://leetcode.com/problems/unique-paths-ii/description

### Problem Statement

Given an `m x n` integer array `grid`, a robot is initially located at the top-left corner `(0, 0)` and needs to reach the bottom-right corner `(m-1, n-1)`. The robot can only move either **down** or **right** at any point in time.

An obstacle and space are marked as `1` and `0` respectively in the grid. A path that the robot takes cannot include any square that is an obstacle.

**Task**: Return the number of possible unique paths that the robot can take to reach the bottom-right corner.

The test cases are generated so that the answer will be less than or equal to $2 \times 10^9$.

### Examples

**Example 1:**
```
Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3×3 grid above.
There are two ways to reach the bottom-right corner:
1. Right → Right → Down → Down
2. Down → Down → Right → Right
```

**Example 2:**
```
Input: obstacleGrid = [[0,1],[0,0]]
Output: 1
```

### Constraints

- $1 \leq m, n \leq 100$
- $m = \text{len}(\text{obstacleGrid})$
- $n = \text{len}(\text{obstacleGrid}[i])$
- `obstacleGrid[i][j]` is either `0` or `1`

---

## Observations

1. **DP Substructure**: The number of unique paths to cell `(i, j)` depends only on:
   - The number of paths to `(i-1, j)` (from above)
   - The number of paths to `(i, j-1)` (from left)
   - Whether cell `(i, j)` contains an obstacle

2. **Obstacle Handling**: If a cell contains an obstacle (`grid[i][j] == 1`), it contributes `0` paths regardless of previous values.

3. **Base Cases**:
   - If the starting cell `(0, 0)` is an obstacle, return `0`
   - The first column can only be reached by moving down, so if an obstacle is encountered, all cells below it have `0` paths
   - The first row can only be reached by moving right, so if an obstacle is encountered, all cells to the right have `0` paths

4. **Recurrence Relation**:
   $$dp[i][j] = \begin{cases} 
   0 & \text{if } grid[i][j] == 1 \\
   dp[i-1][j] + dp[i][j-1] & \text{otherwise}
   \end{cases}$$

5. **Time & Space Complexity**:
   - **Time**: $O(m \times n)$ - visit each cell once
   - **Space**: $O(m \times n)$ - DP table

---

## Solution

### Approach: Dynamic Programming (Bottom-Up Tabulation)

The solution uses a 2D DP table where `dp[i][j]` represents the number of unique paths to reach cell `(i, j)`.

**Algorithm Steps:**

1. **Initialize DP table**: Create an `m × n` table filled with zeros.

2. **Fill first column**: For each row `i` in column `0`:
   - If an obstacle is encountered, mark all subsequent rows as `0` (unreachable)
   - Otherwise, the value is `1` (can only reach via moving down from above)

3. **Fill first row**: For each column `j` in row `0`:
   - If an obstacle is encountered, mark all subsequent columns as `0` (unreachable)
   - Otherwise, the value is `1` (can only reach via moving right from left)

4. **Fill remaining cells**: For each cell `(i, j)` where `i ≥ 1` and `j ≥ 1`:
   - If `grid[i][j] == 1`, set `dp[i][j] = 0` (blocked)
   - Otherwise, set `dp[i][j] = dp[i-1][j] + dp[i][j-1]` (sum of paths from above and left)

5. **Return result**: `dp[m-1][n-1]` contains the answer

**Key Insight**: Once an obstacle is encountered in the first row or column, all subsequent cells in that row/column become unreachable because there's only one way to traverse them (straight across).

---

## Tags

- Dynamic Programming
- Grid/2D Array
- Path Counting
- Obstacle Handling

## Observations

## Solution

# Tags

