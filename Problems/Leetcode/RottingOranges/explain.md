## Problem

https://leetcode.com/problems/rotting-oranges/description/

You are given an **m x n grid** where each cell can have one of three values:
- **0**: representing an empty cell
- **1**: representing a fresh orange
- **2**: representing a rotten orange

Every minute, any fresh orange that is **4-directionally adjacent** to a rotten orange becomes rotten.

**Goal**: Return the minimum number of minutes that must elapse until no cell has a fresh orange. If it's impossible to rot all fresh oranges, return **-1**.

### Examples

**Example 1:**
```
Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
```
The rotten orange at (0,0) spreads to adjacent fresh oranges level by level, taking 4 minutes total.

**Example 2:**
```
Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
```
The fresh orange at (2,0) is isolated (only reachable diagonally), so it can never rot.

**Example 3:**
```
Input: grid = [[0,2]]
Output: 0
```
No fresh oranges exist initially, so the answer is 0.

### Constraints
- `1 <= m, n <= 10`
- `grid[i][j]` is 0, 1, or 2

## Observations

1. **Multi-Source BFS Pattern**: This is a classic multi-source BFS problem. All rotten oranges spread simultaneously, so we start with all rotten oranges as initial sources.

2. **Level-Order Traversal**: Each "level" in the BFS represents one minute of time. We process all rotten oranges at the current level before moving to the next level.

3. **Rotten Count Tracking**: We need to track:
   - Total number of fruits (fresh + rotten)
   - Number of fruits that have been rotted so far
   - When `rotten_count == total_fruits`, all oranges are rotten

4. **Early Termination**: 
   - If all oranges are already rotten at the start, return 0 immediately
   - If we reach a state where all oranges are rotten, return the elapsed time
   - If BFS completes but not all oranges are rotten, some are unreachable → return -1

5. **Time Increment**: We increment the time counter at the end of each level (after processing all oranges that became rotten in that minute).

## Solution

### Algorithm: Multi-Source BFS

**Key Idea**: Treat all initial rotten oranges as sources in a BFS. Expand outward level-by-level, where each level represents one minute.

```python
from collections import deque
from typing import List

class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        
        def dfs() -> int:
            q = deque()
            
            # Step 1: Count total fruits and find all initial rotten oranges
            total_fruit = 0
            rotten_fruit = 0
            for i in range(m):
                for j in range(n):
                    if grid[i][j] == 1:
                        total_fruit += 1
                    if grid[i][j] == 2:
                        total_fruit += 1
                        rotten_fruit += 1
                        q.append((i, j))
            
            # Step 2: Handle edge case - all oranges already rotten
            if rotten_fruit == total_fruit:
                return 0
            
            # Step 3: BFS level-by-level (each level = 1 minute)
            times = 0
            while q:
                size = len(q)  # Process all oranges that rotted in current minute
                
                # Spread rotting to adjacent fresh oranges
                for _ in range(size):
                    r, c = q.popleft()
                    
                    # Check all 4 directions
                    for nr, nc in [(r-1, c), (r+1, c), (r, c-1), (r, c+1)]:
                        # Boundary check
                        if nr >= 0 and nr < m and nc >= 0 and nc < n:
                            # Rot fresh oranges and add to queue
                            if grid[nr][nc] == 1:
                                rotten_fruit += 1
                                grid[nr][nc] = 2
                                q.append((nr, nc))
                
                # Increment time after processing this level
                times += 1
                
                # Check if all oranges are now rotten
                if rotten_fruit == total_fruit:
                    return times
            
            # If we exit the loop without rotting all fruits
            return -1
        
        return dfs()
```

### Step-by-Step Walkthrough

**Given**: `grid = [[2,1,1],[1,1,0],[0,1,1]]`

1. **Initialization**:
   - Scan grid: find `total_fruit = 7`, `rotten_fruit = 1`
   - Queue: `[(0, 0)]` (starting with the rotten orange)

2. **Minute 1** (First BFS level):
   - Process (0, 0): Check neighbors → (0, 1) and (1, 0) are fresh
   - Mark both as rotten: `grid[0][1] = 2`, `grid[1][0] = 2`
   - Queue: `[(0, 1), (1, 0)]`, `rotten_fruit = 3`, `times = 1`

3. **Minute 2**:
   - Process (0, 1) and (1, 0): Find fresh neighbors
   - Mark (0, 2), (1, 1) as rotten
   - Queue: `[(0, 2), (1, 1)]`, `rotten_fruit = 5`, `times = 2`

4. **Minute 3**:
   - Process (0, 2) and (1, 1): Find fresh neighbor (2, 1)
   - Mark (2, 1) as rotten
   - Queue: `[(2, 1)]`, `rotten_fruit = 6`, `times = 3`

5. **Minute 4**:
   - Process (2, 1): Find fresh neighbor (2, 2)
   - Mark (2, 2) as rotten
   - Queue: `[(2, 2)]`, `rotten_fruit = 7`, `times = 4`

6. **Check**: `rotten_fruit (7) == total_fruit (7)` → **Return 4**

### Complexity Analysis

- **Time Complexity**: **O(m × n)**
  - We visit each cell at most once during BFS
  - Initial scan of grid is O(m × n)
  - Total: O(m × n)

- **Space Complexity**: **O(m × n)**
  - Queue can contain at most all cells in the grid
  - In worst case (all cells rotten), queue size is O(m × n)

# Tags

- **Algorithm**: BFS, Multi-Source BFS
- **Pattern**: Level-Order Traversal, Graph Traversal
- **Data Structure**: Queue, 2D Grid
- **Difficulty**: Medium

