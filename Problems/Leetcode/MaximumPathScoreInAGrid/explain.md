## Problem

https://leetcode.com/problems/maximum-path-score-in-a-grid/description

You are given an `m x n` grid where each cell contains one of the values **0**, **1**, or **2**. You are also given an integer `k`.

You start from the **top-left corner** `(0, 0)` and want to reach the **bottom-right corner** `(m - 1, n - 1)` by moving only **right** or **down**.

Each cell contributes a specific **score** and incurs an associated **cost**:
- **0**: adds 0 to your score and costs 0
- **1**: adds 1 to your score and costs 1
- **2**: adds 2 to your score and costs 1

**Return** the maximum score achievable without exceeding a total cost of `k`, or **-1** if no valid path exists.

**Note**: If you reach the last cell but the total cost exceeds `k`, the path is invalid.

### Constraints:
- `1 <= m, n <= 200`
- `0 <= k <= 1000`
- `grid[0][0] == 0`
- `0 <= grid[i][j] <= 2`

### Examples:

**Example 1:**
```
Input: grid = [[0, 1],[2, 0]], k = 1
Output: 2
Explanation:
The optimal path is (0,0) → (1,0) → (1,1)
- (0,0): score=0, cost=0
- (1,0): score=2, cost=1
- (1,1): score=0, cost=0
Total score = 2, Total cost = 1 ✓
```

**Example 2:**
```
Input: grid = [[0, 1],[1, 2]], k = 1
Output: -1
Explanation:
There is no path to (1,1) without exceeding cost k=1.
```

## Observations

1. **State Representation**: This is a path-finding problem where we need to track three dimensions:
   - Current position: `(row, col)`
   - Accumulated cost: remaining budget constraint
   - The score we've accumulated so far

2. **Cost vs Score Decoupling**: 
   - Cell value 0: score=0, cost=0 (free transit)
   - Cell value 1: score=1, cost=1 (1:1 ratio)
   - Cell value 2: score=2, cost=1 (2:1 ratio, best value)

3. **Optimal Substructure**: The maximum score to reach the destination from position `(r, c)` with remaining cost budget depends only on:
   - The values at positions we can reach from `(r, c)`
   - Our remaining cost budget
   - This suggests **Dynamic Programming**

4. **Direction Constraints**: Only moving right or down limits the search space and allows us to process in a specific order (bottom-right to top-left).

5. **Cost Constraint**: We must track the cost spent at each state. The state becomes `(row, col, cost_spent)` and we want to maximize score subject to `cost_spent <= k`.

6. **Memoization vs Tabulation**: 
   - We can use recursive DP with memoization (top-down) indexed by `(r, c, cost)`
   - Or use iterative DP (bottom-up) with a 3D table `dp[r][c][cost]`
   - Tabulation is more efficient here since we process in reverse order

## Solution

### Approach: Dynamic Programming (Tabulation - Bottom-Up)

**State Definition:**
```
dp[r][c][cost] = maximum score we can achieve reaching (m-1, n-1) 
                 starting from position (r, c) with 'cost' already spent
```

**Key Insight:**
- We process from bottom-right to top-left
- For each cell, we try moving right or down
- We track how much cost we've accumulated so far
- `dp[r][c][cost] = grid[r][c] + max(dp[r][c+1][...], dp[r+1][c][...])`

**Algorithm:**

1. **Initialize**: Create a 3D DP table with dimensions `(m+1) × (n+1) × (k+2)` initialized to `-1`
   - Extra row and column as boundaries
   - Extra cost dimension for safety

2. **Base Case**: Fill the last cell `(m-1, n-1)`
   - For each possible cost already spent, check if we can afford the cell
   - `dp[m-1][n-1][cost] = grid[m-1][n-1]` if `cost + need_cost <= k`

3. **Fill Table** (bottom-right to top-left):
   - For each position `(r, c)` going backwards
   - For each cost value from `k` down to `0` (reverse order is important for correctness)
   - Calculate the cost needed for current cell: `need_cost = 1 if grid[r][c] != 0 else 0`
   - Try both directions:
     - Right: `dp[r][c+1][cost + need_cost]`
     - Down: `dp[r+1][c][cost + need_cost]`
   - Take the maximum valid result: `dp[r][c][cost] = grid[r][c] + max(right_score, down_score)`

4. **Answer**: `dp[0][0][0]` (starting at top-left with cost 0 spent)

**Time Complexity:** $O(m \times n \times k)$
- Three nested loops over rows, columns, and cost budget

**Space Complexity:** $O(m \times n \times k)$
- 3D DP table

### Code

```python
class Solution:
    def maxPathScore(self, grid: List[List[int]], k: int) -> int:
        m, n = len(grid), len(grid[0])
        
        # dp[r][c][cost] = max score from (r, c) to (m-1, n-1) 
        #                  with 'cost' already spent
        dp = [[[-1] * (k + 2) for _ in range(n + 1)] for _ in range(m + 1)]
        
        # Base case: fill the bottom-right corner
        for cost in range(k + 1):
            need_cost = (grid[m - 1][n - 1] != 0)
            if cost + need_cost <= k:
                dp[m - 1][n - 1][cost] = grid[m - 1][n - 1]
        
        # Fill the table bottom-right to top-left
        for r in range(m - 1, -1, -1):
            for c in range(n - 1, -1, -1):
                need_cost = (grid[r][c] != 0)
                for cost in range(k, -1, -1):
                    # Try moving right
                    right = dp[r][c + 1][cost + need_cost]
                    if right != -1:
                        dp[r][c][cost] = max(dp[r][c][cost], grid[r][c] + right)
                    
                    # Try moving down
                    down = dp[r + 1][c][cost + need_cost]
                    if down != -1:
                        dp[r][c][cost] = max(dp[r][c][cost], grid[r][c] + down)
        
        return dp[0][0][0]
```

### Why This Works

1. **Validity Check**: A path is valid only if total cost ≤ k. We ensure this by tracking cost and checking before using previous results.

2. **Optimality**: By processing bottom-right to top-left and considering all possible ways to reach the destination, we guarantee finding the maximum score.

3. **Cost Dimension**: Including cost as a dimension allows us to differentiate between reaching the same cell with different cost budgets remaining, which affects future choices.

4. **Boundary Handling**: The extra row/column initialized to -1 naturally handles out-of-bounds cases, returning -1 for invalid paths.

### Example Walkthrough

**Example 1: grid = [[0, 1],[2, 0]], k = 1**

```
Initial setup:
dp[1][1][0] = 0 (last cell, cost 0)
dp[1][1][1] = 0 (last cell, cost 1)

Process (1, 0):
  grid[1][0] = 2, need_cost = 1
  dp[1][0][0] = 2 + dp[1][1][1] = 2 + 0 = 2

Process (0, 1):
  grid[0][1] = 1, need_cost = 1
  dp[0][1][0] = 1 + dp[1][1][1] = 1 + 0 = 1

Process (0, 0):
  grid[0][0] = 0, need_cost = 0
  dp[0][0][0] = 0 + max(dp[0][1][0], dp[1][0][0]) = 0 + max(1, 2) = 2

Answer: dp[0][0][0] = 2 ✓
```

# Tags
- Dynamic Programming
- Grid DP
- Cost-Constrained Optimization
- Bottom-Up Tabulation

