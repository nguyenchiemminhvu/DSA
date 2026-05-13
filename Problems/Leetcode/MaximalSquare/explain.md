## Problem

https://leetcode.com/problems/maximal-square/description

Given an **m x n binary matrix** filled with 0's and 1's, find the **largest square** containing only 1's and return its **area**.

### Examples

**Example 1:**
```
Input: matrix = [["1","0","1","0","0"],
                 ["1","0","1","1","1"],
                 ["1","1","1","1","1"],
                 ["1","0","0","1","0"]]
Output: 4
Explanation: The largest square has side length 2, so area = 4
```

**Example 2:**
```
Input: matrix = [["0","1"],
                 ["1","0"]]
Output: 1
Explanation: The largest square has side length 1, so area = 1
```

**Example 3:**
```
Input: matrix = [["0"]]
Output: 0
```

### Constraints
- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 300`
- `matrix[i][j]` is '0' or '1'

## Observations

1. **State Definition**: For each cell `(i, j)`, we need to determine the **side length of the largest square** with bottom-right corner at `(i, j)` and containing only 1's.

2. **Key Insight**: A square at position `(i, j)` can exist only if:
   - The cell itself is '1'
   - There exists a square of side length `s-1` at three adjacent positions: bottom `(i+1, j)`, right `(i, j+1)`, and diagonal `(i+1, j+1)`
   
3. **Recurrence Relation**: 
   ```
   dp[i][j] = 1 + min(dp[i+1][j], dp[i][j+1], dp[i+1][j+1])  if grid[i][j] == '1'
   dp[i][j] = 0                                                 if grid[i][j] == '0'
   ```
   
   The reasoning: If we know the maximum squares at the three neighbors, the maximum square ending at `(i, j)` is limited by the smallest of those three neighbors (forming the constraint on all three sides).

4. **Processing Order**: We must process from **bottom-right to top-left** to ensure dependencies are resolved before computation.

5. **Result**: The answer is `max_side_length²`

## Solution

### Approach 1: Dynamic Programming (Bottom-Up)

**Time Complexity**: O(m × n)  
**Space Complexity**: O(m × n)

```python
class Solution:
    def maximalSquare(self, grid: List[List[str]]) -> int:
        m, n = len(grid), len(grid[0])
        
        # dp[i][j] represents the side length of the largest square
        # with bottom-right corner at (i, j)
        dp = [[0 for _ in range(n + 1)] for _ in range(m + 1)]
        
        max_side = 0
        
        # Process from bottom-right to top-left
        for i in range(m - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                if grid[i][j] == '0':
                    dp[i][j] = 0
                else:
                    # Side length = 1 + min of three neighbors
                    dp[i][j] = 1 + min(dp[i + 1][j], dp[i][j + 1], dp[i + 1][j + 1])
                
                max_side = max(max_side, dp[i][j])
        
        return max_side ** 2
```

**Explanation**:
- We create a DP table where `dp[i][j]` stores the side length of the largest square ending at `(i, j)`
- We initialize with an extra row and column of zeros (boundary condition)
- We iterate from bottom-right to top-left so that when we compute `dp[i][j]`, the three dependencies below and to the right are already computed
- For each '1', we update its value as `1 + min(neighbors)` which represents extending the square from the three directions
- We track the maximum side length and return its square

**Trace Example** (Example 1):
```
Grid:                          DP table:
1 0 1 0 0                       1 0 1 0 0
1 0 1 1 1         →             1 0 1 1 1
1 1 1 1 1                       1 1 2 2 2
1 0 0 1 0                       1 0 0 1 0

max_side = 2, answer = 4
```

### Approach 2: Memoized Recursion (Top-Down)

**Time Complexity**: O(m × n)  
**Space Complexity**: O(m × n)

```python
class Solution:
    def maximalSquare(self, grid: List[List[str]]) -> int:
        m, n = len(grid), len(grid[0])
        memo = {}
        
        def dfs(i: int, j: int) -> int:
            # Base cases
            if i >= m or j >= n or grid[i][j] == '0':
                return 0
            
            # Check memo
            if (i, j) in memo:
                return memo[(i, j)]
            
            # Recursive: max square side = 1 + min of three directions
            down = dfs(i + 1, j)
            right = dfs(i, j + 1)
            diagonal = dfs(i + 1, j + 1)
            
            result = 1 + min(down, right, diagonal)
            memo[(i, j)] = result
            return result
        
        max_side = 0
        for i in range(m):
            for j in range(n):
                max_side = max(max_side, dfs(i, j))
        
        return max_side ** 2
```

## Complexity Analysis

| Aspect | DP Bottom-Up | DP Top-Down |
|--------|-------------|-----------|
| **Time** | O(m × n) | O(m × n) |
| **Space** | O(m × n) for DP array | O(m × n) for memo + O(m × n) for recursion stack |
| **Cache** | Implicit through iteration | Explicit memoization |

## Key Insights

1. **Why min(three_neighbors)?** Because a square is defined by its four sides. If any neighboring square is smaller, the current square is bounded by that constraint.

2. **Bottom-Right Processing**: We process from bottom-right because every cell depends on cells below and to the right.

3. **Square Area**: We return `side_length²` not `side_length`, as the problem asks for area, not side length.

# Tags

`Dynamic Programming` `Memoization` `Matrix` `Bottom-Up DP` `Top-Down DP`

