## Problem

https://leetcode.com/problems/detect-cycles-in-2d-grid

Given a 2D array of characters `grid` of size `m x n`, find if there exists any cycle consisting of the same value in the grid.

**Cycle Definition:**
- A cycle is a path of length 4 or more in the grid that starts and ends at the same cell
- From a given cell, you can move to one of the four adjacent cells (up, down, left, right) if it has the same value as the current cell
- **Critical constraint**: You cannot move to the cell visited in your last move (the cell you came from)
  - Example: (1,1) → (1,2) → (1,1) is **invalid** because we're revisiting the immediately previous cell

**Return:** `true` if any cycle of the same value exists, `false` otherwise

**Constraints:**
- 1 ≤ m, n ≤ 500
- grid consists only of lowercase English letters

**Examples:**

**Example 1:**
```
Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
Output: true
Explanation: There are two valid cycles of 'a' (outer ring) and one valid cycle of 'b' (center 2x2 square)
```

**Example 2:**
```
Input: grid = [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
Output: true
Explanation: The 'c' characters form a cycle
```

**Example 3:**
```
Input: grid = [["a","b","b"],["b","z","b"],["b","b","a"]]
Output: false
Explanation: No characters have a cycle
```

## Observations

1. **Graph Problem**: This is essentially detecting a cycle in an undirected graph where:
   - Nodes are grid cells
   - Edges connect adjacent cells with the same value
   - The "no revisiting previous cell" constraint accounts for the directed nature of our traversal

2. **Minimum Cycle Length**: A cycle must have length ≥ 4 because:
   - You need at least 4 moves to return to the starting cell without immediately backtracking
   - A path like A → B → A is invalid (length 2)

3. **DFS with Parent Tracking**: The key insight is using Depth-First Search while tracking:
   - The **parent cell** (previous cell in traversal) to avoid immediate backtracking
   - The **visited** set to detect when we reach a previously explored cell (indicating a cycle)

4. **Cycle Detection Logic**: 
   - When doing DFS, if we encounter a cell that:
     - Has the same value as current cell
     - Is not the cell we came from (parent)
     - Has already been visited
   - Then we've found a cycle!

5. **Why DFS works better than BFS here**:
   - DFS naturally tracks the path and parent relationship
   - We can detect cycles by encountering a visited cell that's not our immediate parent
   - The "parent skip" prevents false positive cycle detection

6. **Connected Components**: We need to try starting DFS from every unvisited cell:
   - Different characters form independent groups
   - A cycle might exist in any connected component
   - Once a cell is visited in one DFS, we skip it (already checked that component)

## Solution

### Approach: DFS with Visited Tracking and Parent Avoidance

The algorithm uses Depth-First Search to traverse the grid:

1. **Initialization**: Create a `visited` 2D array to track explored cells
2. **For each cell**: If not visited, start a DFS traversal
3. **DFS Logic**:
   - Mark current cell as visited
   - Explore all 4 adjacent cells
   - For each adjacent cell with the same value:
     - Skip if it's the parent (previous cell) - avoid immediate backtracking
     - If already visited → **cycle detected**, return True
     - Otherwise, recursively continue DFS
4. **Return**: True if any DFS finds a cycle, False otherwise

### Code

```python
class Solution:
    def containsCycle(self, grid: List[List[str]]) -> bool:
        m, n = len(grid), len(grid[0])
        visited = [[False] * n for _ in range(m)]
        
        def dfs(r, c, pr, pc, char):
            """
            DFS helper function
            r, c: current cell coordinates
            pr, pc: parent cell coordinates (cell we came from)
            char: the character value we're looking for cycles of
            """
            # Mark current cell as visited
            visited[r][c] = True
            
            # Explore all 4 directions
            for dr, dc in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                nr, nc = r + dr, c + dc
                
                # Check bounds and character match
                if 0 <= nr < m and 0 <= nc < n and grid[nr][nc] == char:
                    
                    # Skip the previous cell (parent) - prevent immediate backtracking
                    if nr == pr and nc == pc:
                        continue
                    
                    # If already visited → cycle found!
                    if visited[nr][nc]:
                        return True
                    
                    # Continue DFS from neighbor
                    if dfs(nr, nc, r, c, char):
                        return True
            
            return False
        
        # Try starting DFS from every unvisited cell
        for i in range(m):
            for j in range(n):
                if not visited[i][j]:
                    if dfs(i, j, -1, -1, grid[i][j]):
                        return True
        
        return False
```

### How It Works Step-by-Step

**Example: grid = [["a","a","a"],["a","b","a"],["a","a","a"]]**

1. Start DFS from (0, 0) with char='a', parent=(-1, -1)
2. Visit (0, 0), mark as visited
3. Explore neighbors: move to (1, 0) with parent=(0, 0)
4. Continue building path: (1, 0) → (2, 0) → (2, 1) → (2, 2) → (1, 2) → (0, 2) → (0, 1)
5. From (0, 1), we can reach (1, 1) which has 'b' - skip (different char)
6. From (0, 1), we can reach (0, 0) which is:
   - Same character ('a')
   - NOT the parent (parent was from different direction)
   - Already visited → **Cycle detected!**

### Complexity Analysis

**Time Complexity: O(m × n)**
- Each cell is visited at most once
- Each cell's 4 neighbors are checked
- Total operations: O(m × n)

**Space Complexity: O(m × n)**
- `visited` array: O(m × n)
- Recursive call stack (worst case): O(m × n) in a long path

### Key Takeaways

✅ **Why parent tracking is crucial**: Without it, (1, 1) → (1, 2) → (1, 1) would falsely detect a cycle  
✅ **Why visited tracking is crucial**: Detects actual cycles, not just paths  
✅ **Why we start from every unvisited cell**: Handles disconnected components with different characters  
✅ **Why minimum length is 4**: The parent constraint naturally prevents cycles shorter than 4

# Tags
DFS, Graph Cycle Detection, Visited Array, Backtracking, Grid Traversal

