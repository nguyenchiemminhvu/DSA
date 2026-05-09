## Problem

https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/description

You are given an `m × n` matrix `maze` (0-indexed) with:
- Empty cells represented as `'.'`
- Walls represented as `'+'`

You start at an entrance position `entrance = [entrancerow, entrancecol]`.

**Movement Rules:**
- You can move one cell in any of 4 directions (up, down, left, right)
- You cannot step into walls or outside the maze boundaries

**Goal:** Find the minimum number of steps to reach an exit.
- An exit is an empty cell (`'.'`) at the border of the maze
- The entrance cell does not count as an exit

**Return:** The number of steps in the shortest path, or `-1` if no exit is reachable.

**Examples:**

Example 1:
```
Input: maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance = [1,2]
Output: 1
Explanation: Starting at [1,2], moving up 1 step reaches [0,2] which is an exit.
```

Example 2:
```
Input: maze = [["+","+","+"],[".",".","."],["+","+","+"]], entrance = [1,0]
Output: 2
Explanation: Must move right 2 steps to reach [1,2], the only exit.
```

Example 3:
```
Input: maze = [[".","+"]], entrance = [0,0]
Output: -1
Explanation: The starting position is at the border but doesn't count as an exit.
```

**Constraints:**
- `maze.length == m` and `maze[i].length == n`
- `1 <= m, n <= 100`
- `maze[i][j]` is either `'.'` or `'+'`
- `entrance` is always an empty cell

## Observations

1. **Shortest Path Problem:** This is a classic shortest path problem in an unweighted grid, which naturally suggests BFS (Breadth-First Search).

2. **Border Condition:** An exit must be:
   - An empty cell (`.`)
   - Located at any border (row 0, row m-1, column 0, or column n-1)
   - Different from the starting entrance position

3. **Level-by-Level Exploration:** BFS explores cells in order of distance from the source, ensuring the first exit found is the nearest one.

4. **Visited Set Tracking:** We need to mark visited cells to avoid revisiting them and getting trapped in cycles.

5. **Early Termination:** Once we reach any valid exit, we can immediately return the step count without exploring further.

## Solution

**Approach: Breadth-First Search (BFS)**

The key insight is that BFS naturally explores cells level by level, where each level represents cells at the same distance from the entrance. The first exit we encounter during BFS traversal is guaranteed to be the nearest one.

**Algorithm:**
1. Initialize a queue with the starting entrance position
2. Mark the entrance as visited
3. Process cells level by level (using queue size to track levels)
4. For each cell at the current level:
   - Check if it's an exit (at border AND is empty AND not the entrance)
   - If yes, return the current step count
   - Otherwise, add all unvisited neighbors (empty cells) to the queue
5. Increment step count after processing all cells at current level
6. If queue becomes empty without finding an exit, return -1

**Code:**

```python
from collections import deque
from typing import List

class Solution:
    def nearestExit(self, maze: List[List[str]], entrance: List[int]) -> int:
        m, n = len(maze), len(maze[0])

        def bfs() -> int:
            steps = 0
            q = deque()
            q.append((entrance[0], entrance[1]))
            visited = [[False] * n for i in range(m)]
            visited[entrance[0]][entrance[1]] = True
            
            while q:
                size = len(q)  # Number of cells at current level
                
                for _ in range(size):
                    r, c = q.popleft()

                    # Check if current position is an exit
                    # An exit is at the border AND is an empty cell AND is not the entrance
                    if (r == 0 or r == m - 1 or c == 0 or c == n - 1):
                        if grid[r][c] == '.':
                            if r != entrance[0] or c != entrance[1]:
                                return steps
                    
                    # Explore all 4 neighbors
                    for nr, nc in [(r-1, c), (r+1, c), (r, c-1), (r, c+1)]:
                        # Check bounds, is empty, and not visited
                        if nr >= 0 and nr < m and nc >= 0 and nc < n:
                            if maze[nr][nc] == '.' and not visited[nr][nc]:
                                visited[nr][nc] = True
                                q.append((nr, nc))
                
                steps += 1
            
            return -1
        
        return bfs()
```

**Detailed Walkthrough:**

Example 1: `maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance = [1,2]`

```
Grid visualization:
+  +  .  +
.  .  .  +
+  +  +  .

Starting at entrance [1,2] (step 0)
```

- **Step 0:** Queue = [(1,2)], Check [1,2]: Not at border, skip. Explore neighbors.
  - Valid neighbors: [0,2] (empty, unvisited), [1,1] (empty, unvisited), [1,3] (wall, skip)
  - Add to queue: [0,2], [1,1]

- **Step 1:** Queue = [(0,2), (1,1)]
  - Process [0,2]: At border (row 0), is empty, not entrance → **RETURN 1**

**Time Complexity:** O(m × n)
- Each cell is visited at most once

**Space Complexity:** O(m × n)
- Visited array: O(m × n)
- Queue can contain at most O(m × n) cells in worst case

# Tags
#BFS #Shortest-Path #Graph #Grid

