## Problem

https://leetcode.com/problems/unique-paths/description

```
There is a robot on an m x n grid. The robot is initially located at the 
top-left corner (i.e., grid[0][0]). The robot tries to move to the 
bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move 
either down or right at any point in time.

Given the two integers m and n, return the number of possible unique paths 
that the robot can take to reach the bottom-right corner.

The test cases are generated so that the answer will be less than or equal 
to 2 * 10^9.

Constraints:
- 1 <= m, n <= 100

Example 1:
Input: m = 3, n = 7
Output: 28

Example 2:
Input: m = 3, n = 2
Output: 3
Explanation: From the top-left corner, there are a total of 3 ways to 
reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down
```

## Observations

1. **Path Constraints**: The robot can only move down or right, meaning to reach 
   position (m-1, n-1) from (0, 0), we need exactly (m-1) down moves and (n-1) 
   right moves.

2. **Subproblem Property**: The number of ways to reach any cell (i, j) depends 
   only on the number of ways to reach (i-1, j) and (i, j-1). This is a classic 
   dynamic programming structure:
   - `ways[i][j] = ways[i-1][j] + ways[i][j-1]`

3. **Base Cases**: 
   - All cells in the first row can only be reached in 1 way (move right)
   - All cells in the first column can only be reached in 1 way (move down)

4. **Grid Independence**: The grid values don't matter—we only care about the 
   dimensions. Any path is valid since there are no obstacles.

5. **Combinatorial Insight**: This is essentially a combinatorial problem. To go 
   from (0, 0) to (m-1, n-1), we need to choose (m-1) positions out of (m-1+n-1) 
   total moves for "down" moves (or equivalently, choose (n-1) positions for 
   "right" moves). This gives us C(m+n-2, m-1) unique paths.

## Solution

### Approach 1: Dynamic Programming (2D Array)

**Time Complexity**: O(m × n)  
**Space Complexity**: O(m × n)

```python
class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        # Create a 2D DP table
        dp = [[0 for _ in range(n)] for _ in range(m)]
        
        # Base case: first column - only one way to reach each cell (move down)
        for i in range(m):
            dp[i][0] = 1
        
        # Base case: first row - only one way to reach each cell (move right)
        for i in range(n):
            dp[0][i] = 1
        
        # Fill the DP table
        # For each cell, the number of ways is the sum of ways from top and left
        for i in range(1, m):
            for j in range(1, n):
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1]
        
        return dp[m - 1][n - 1]
```

**How it works**:
- We build a table where `dp[i][j]` represents the number of ways to reach 
  position (i, j)
- We initialize the first row and first column with 1 (only one path to reach 
  those cells)
- For every other cell, we add the number of paths from the cell above and the 
  cell to the left
- The answer is at `dp[m-1][n-1]`

**Example walkthrough (m=3, n=7)**:
```
    0   1   2   3   4   5   6
0   1   1   1   1   1   1   1
1   1   2   3   4   5   6   7
2   1   3   6  10  15  21  28
```

Each cell is the sum of the cell above and the cell to the left.

### Approach 2: Memoization (Top-down DP)

**Time Complexity**: O(m × n)  
**Space Complexity**: O(m × n)

```python
class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        mem = {}
        
        def F(r: int, c: int) -> int:
            # Out of bounds
            if r < 0 or c < 0:
                return 0
            # Base cases: reached first row or first column
            if r == 0 or c == 0:
                return 1
            # Check memoization
            if (r, c) in mem:
                return mem[(r, c)]
            # Recurrence: sum of paths from above and from left
            cur = F(r - 1, c) + F(r, c - 1)
            mem[(r, c)] = cur
            return cur
        
        return F(m - 1, n - 1)
```

**How it works**:
- We use a recursive approach with memoization
- For position (r, c), we calculate the sum of paths from (r-1, c) and (r, c-1)
- We cache results to avoid recalculating the same subproblems
- This is a top-down approach compared to the bottom-up DP solution

### Approach 3: Mathematical Combinatorics

**Time Complexity**: O(min(m, n))  
**Space Complexity**: O(1)

This is the optimal solution! Since we need exactly (m-1) down moves and (n-1) 
right moves, the total number of unique paths is the number of ways to arrange 
these moves, which is a combination:

$$\text{uniquePaths}(m, n) = C(m+n-2, m-1) = \frac{(m+n-2)!}{(m-1)! \cdot (n-1)!}$$

```python
from math import comb

class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        return comb(m + n - 2, m - 1)
```

Or implement combination manually:

```python
class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        # Calculate C(m+n-2, m-1) = (m+n-2)! / ((m-1)! * (n-1)!)
        # We optimize by calculating C(n, k) where k = min(m-1, n-1)
        numerator = 1
        denominator = 1
        for i in range(min(m - 1, n - 1)):
            numerator *= (m + n - 2 - i)
            denominator *= (i + 1)
        return numerator // denominator
```

## Comparison

| Approach | Time | Space | Pros | Cons |
|----------|------|-------|------|------|
| 2D DP | O(m×n) | O(m×n) | Easy to understand, standard DP | Uses extra space |
| Memoization | O(m×n) | O(m×n) | Intuitive recursion | Stack overhead |
| Combinatorics | O(min(m,n)) | O(1) | **Optimal**, least resources | Requires mathematical insight |

## Key Insights

- **DP Recurrence**: `dp[i][j] = dp[i-1][j] + dp[i][j-1]`
- **Base Cases**: First row and column all have value 1
- **Optimal Solution**: Use combinatorics for best performance (O(min(m,n)) time)
- **Similar Problems**: Climbing Stairs, Minimum Path Sum, Paths with Obstacles

# Tags

#dynamic-programming #combinatorics #grid-paths #math #medium

