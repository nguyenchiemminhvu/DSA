## Problem

https://leetcode.com/problems/surrounded-regions/description

Given an `m x n` matrix `board` containing letters `'X'` and `'O'`, you need to capture all regions of `'O'` that are completely surrounded by `'X'`.

**Key Definitions:**
- **Connected**: A cell is connected to adjacent cells horizontally or vertically (not diagonally)
- **Region**: Multiple connected `'O'` cells form a region
- **Surrounded**: A region is surrounded if NONE of its `'O'` cells touch the edge of the board
- **Capture**: Replace all `'O'` cells in a surrounded region with `'X'` cells (in-place)

**Constraints:**
- `1 <= m, n <= 200`
- `board[i][j]` is either `'X'` or `'O'`
- Modify the board in-place; no return value needed

**Examples:**
```
Example 1:
Input:  [["X","X","X","X"],
         ["X","O","O","X"],
         ["X","X","O","X"],
         ["X","O","X","X"]]

Output: [["X","X","X","X"],
         ["X","X","X","X"],
         ["X","X","X","X"],
         ["X","O","X","X"]]

Explanation: The bottom "O" touches the edge, so it's not surrounded and stays as "O"
```

## Observations

1. **Key Insight**: A region is safe (NOT surrounded) if ANY cell in it touches the board edge. This suggests an inverted approach:
   - Instead of finding surrounded regions, find regions that are NOT surrounded
   - Mark all `'O'` cells connected to edge cells as "safe"
   - Remaining unmarked `'O'` cells are surrounded and should be captured

2. **Graph Traversal Problem**: This is essentially finding connected components in an undirected graph:
   - Cells are nodes
   - Adjacent cells (same value) are connected by edges
   - We need to identify which components touch the boundary

3. **Why Inverted Approach?**
   - Direct approach: Mark all surrounded regions (harder to identify)
   - Inverted approach: Mark all unsurrounded regions (easier - just check boundary connections)
   - Remaining regions are automatically surrounded

4. **Algorithm Strategy**:
   - Start DFS/BFS from all `'O'` cells on the edges
   - Mark all connected `'O'` cells as "visited" (safe)
   - After traversal, any unvisited `'O'` cell is in a surrounded region
   - Convert all unvisited `'O'` cells to `'X'`

5. **Space-Time Tradeoff**:
   - Can use visited array to avoid modifying board during traversal
   - Alternative: Modify board directly or use a marker character temporarily
   - Current approach: O(m*n) space for visited array, O(m*n) time for traversal

## Solution

### Approach: DFS with Boundary-Starting Points

**Algorithm:**
1. Find all `'O'` cells on the boundary of the board
2. For each boundary `'O'`, perform DFS to mark all connected `'O'` cells as "safe"
3. After marking safe regions, iterate through the board and flip any remaining `'O'` to `'X'`

**Why this works:**
- All `'O'` regions that touch the edge cannot be surrounded
- By marking these safe regions first, we ensure only truly surrounded regions remain to be converted

```python
class Solution:
    def solve(self, grid: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        m, n = len(grid), len(grid[0])
        
        # Track visited cells to identify safe regions (connected to boundary)
        visited = [[False for _ in range(n)] for _ in range(m)]

        def dfs(r: int, c: int):
            """Mark all 'O' cells connected to (r,c) as visited (safe)"""
            visited[r][c] = True
            # Check all 4 adjacent cells (up, down, left, right)
            for nr, nc in [(r-1, c), (r+1, c), (r, c-1), (r, c+1)]:
                # If neighbor is in bounds, not visited, and is 'O', continue DFS
                if nr >= 0 and nr < m and nc >= 0 and nc < n:
                    if not visited[nr][nc] and grid[nr][nc] == 'O':
                        dfs(nr, nc)
        
        # Step 1: Mark all 'O' regions connected to the boundary
        # Check top and bottom rows
        for j in range(n):
            if not visited[0][j] and grid[0][j] == 'O':
                dfs(0, j)
            if not visited[m-1][j] and grid[m-1][j] == 'O':
                dfs(m-1, j)
        
        # Check left and right columns (excluding corners already checked)
        for i in range(1, m-1):
            if not visited[i][0] and grid[i][0] == 'O':
                dfs(i, 0)
            if not visited[i][n-1] and grid[i][n-1] == 'O':
                dfs(i, n-1)
        
        # Step 2: Convert unvisited 'O' cells to 'X' (these are surrounded)
        for i in range(m):
            for j in range(n):
                if not visited[i][j] and grid[i][j] == 'O':
                    grid[i][j] = 'X'
```

### Complexity Analysis

- **Time Complexity**: **O(m × n)**
  - Each cell is visited at most once during DFS traversals
  - Final iteration through all cells to convert `'O'` to `'X'`
  
- **Space Complexity**: **O(m × n)**
  - Visited array: O(m × n)
  - DFS recursion stack: O(m × n) in worst case (all cells form one region)

### Alternative Variations

**Option 1: Direct Board Modification (No Extra Space)**
```python
# Instead of visited array, use a temporary marker (e.g., '#')
def dfs(r: int, c: int):
    if r < 0 or r >= m or c < 0 or c >= n or grid[r][c] != 'O':
        return
    grid[r][c] = '#'  # Mark as visited with temporary character
    dfs(r-1, c)
    dfs(r+1, c)
    dfs(r, c-1)
    dfs(r, c+1)

# After DFS, convert:
# '#' back to 'O' (safe regions)
# 'O' to 'X' (surrounded regions)
```

**Option 2: BFS Instead of DFS**
- Use a queue instead of recursion stack
- Prevents potential stack overflow for very large regions
- Same time/space complexity

# Tags

#DFS #BFS #GraphTraversal #DepthFirstSearch #BreadthFirstSearch #ConnectedComponents #Matrix #InPlace #Leetcode-Medium

