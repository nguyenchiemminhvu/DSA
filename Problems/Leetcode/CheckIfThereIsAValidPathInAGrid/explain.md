## Problem

https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/

You are given an m x n grid where each cell represents a street with different connection patterns:

- **1**: connects left and right cells
- **2**: connects upper and lower cells
- **3**: connects left and lower cells
- **4**: connects right and lower cells
- **5**: connects left and upper cells
- **6**: connects right and upper cells

Starting from the upper-left cell (0, 0), determine if there exists a valid path to the bottom-right cell (m - 1, n - 1). A valid path must:
- Only follow the street connections (cannot change streets)
- Connect adjacent cells where both cells' streets have a mutual connection

**Constraints:**
- 1 ≤ m, n ≤ 300
- 1 ≤ grid[i][j] ≤ 6

**Examples:**

Example 1: `grid = [[2,4,3],[6,5,2]]` → `true`
- Can traverse from (0,0) → (1,0) → (1,1) → (1,2) following valid connections

Example 2: `grid = [[1,2,1],[1,2,1]]` → `false`
- (0,0) has street type 1 (left-right), but cannot connect to adjacent cells

Example 3: `grid = [[1,1,2]]` → `false`
- Gets stuck at (0,1) and cannot reach (0,2)

## Observations

1. **Graph Connectivity Problem**: Each cell is a node, and valid connections form edges. We need to determine reachability from (0,0) to (m-1,n-1).

2. **Bidirectional Connection Requirement**: Moving from cell (i,j) to (ni,nj) requires:
   - Cell (i,j) must have an outgoing direction to (ni,nj)
   - Cell (ni,nj) must have a corresponding incoming direction from (i,j)
   - This is verified using the check: `(-dx, -dy) in d_map[grid[ni][nj]]`

3. **Direction Mapping**: Each street type maps to two opposite directions:
   - Type 1: horizontal directions (0,-1) and (0,1)
   - Type 2: vertical directions (-1,0) and (1,0)
   - Types 3-6: corner connections with one horizontal and one vertical direction

4. **Starting Position**: Cell (0,0) determines the initial connections available. If (0,0) is type 1 (horizontal), we can only move left/right from the start, which limits reachability.

5. **DFS Approach**: Using depth-first search with a visited set efficiently explores all possible paths from the start cell. A single valid path is sufficient for the answer.

## Solution

```python
class Solution:
    def hasValidPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        
        # Direction mappings for each street type
        # Each type maps to two relative directions (dr, dc)
        d_map = {
            1: [(0, -1), (0, 1)],      # left, right
            2: [(-1, 0), (1, 0)],      # up, down
            3: [(0, -1), (1, 0)],      # left, down
            4: [(0, 1), (1, 0)],       # right, down
            5: [(-1, 0), (0, -1)],     # up, left
            6: [(-1, 0), (0, 1)]       # up, right
        }
        
        visited = set()
        
        def dfs(i, j):
            # Base case: reached destination
            if (i, j) == (m - 1, n - 1):
                return True
            
            # Mark current cell as visited
            visited.add((i, j))
            
            # Try all possible directions from current street type
            for dx, dy in d_map[grid[i][j]]:
                ni, nj = i + dx, j + dy
                
                # Check bounds and visited status
                if 0 <= ni < m and 0 <= nj < n and (ni, nj) not in visited:
                    # Verify mutual connection: neighbor must have opposite direction
                    # If we move by (dx, dy), neighbor must accept movement by (-dx, -dy)
                    if (-dx, -dy) in d_map[grid[ni][nj]]:
                        if dfs(ni, nj):
                            return True
            
            return False
        
        return dfs(0, 0)
```

**Algorithm Explanation:**

1. **Direction Mapping** (d_map): Pre-compute which directions each street type connects to, making the connection check O(1).

2. **DFS Traversal**: 
   - Start from (0,0) and recursively explore all reachable neighbors
   - For each cell, iterate through its possible directions
   - Check if the neighbor cell exists and hasn't been visited

3. **Mutual Connection Validation**:
   - When moving in direction (dx, dy), the neighbor must be able to accept movement from direction (-dx, -dy)
   - Example: moving right to (0, 1) requires (0, 1) to have a leftward connection
   - This ensures bidirectional street compatibility

4. **Base Cases**:
   - **Success**: Reach (m-1, n-1) - return True immediately
   - **Failure**: Explore all reachable neighbors without finding destination - return False

**Complexity Analysis:**
- **Time**: O(m × n) - each cell visited at most once in worst case
- **Space**: O(m × n) - visited set + recursion call stack in worst case

# Tags
graph, dfs, path-finding, validation

