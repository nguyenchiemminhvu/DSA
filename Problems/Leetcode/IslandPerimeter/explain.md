## Problem

https://leetcode.com/problems/island-perimeter

```
You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.

Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).

The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.

Example 1:

Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
Output: 16
Explanation: The perimeter is the 16 yellow stripes in the image above.

Example 2:

Input: grid = [[1]]
Output: 4

Example 3:

Input: grid = [[1,0]]
Output: 4

Constraints:

row == grid.length
col == grid[i].length
1 <= row, col <= 100
grid[i][j] is 0 or 1.
There is exactly one island in grid.
```

## Observations

1. **Problem Understanding**: We need to calculate the perimeter of a single island in a 2D grid where 1 represents land and 0 represents water.

2. **Perimeter Calculation**: Each land cell contributes to the perimeter based on how many of its 4 sides are exposed to water or the grid boundary.

3. **Key Insight**: A land cell's contribution to perimeter = 4 - (number of adjacent land cells)
   - Each land cell starts with 4 potential perimeter sides
   - For each adjacent land cell, we lose 1 side from the perimeter

4. **Edge Cases**:
   - Single cell island: contributes 4 to perimeter
   - Cells at grid boundaries: sides touching boundaries count toward perimeter
   - Connected land cells: shared borders don't contribute to perimeter

5. **Grid Constraints**: 
   - Only one island exists (no multiple disconnected islands)
   - No "lakes" (water completely surrounded by land)
   - Grid dimensions: 1 ≤ row, col ≤ 100

## Solution

The provided solution uses BFS (Breadth-First Search) to traverse the island and calculate its perimeter:

### Algorithm Breakdown:

1. **Grid Traversal**: Iterate through each cell in the grid to find land cells (value = 1)

2. **BFS Implementation**:
   - When a land cell is found, start BFS from that cell
   - Mark visited cells with value 2 to avoid revisiting
   - Use a queue to process cells level by level

3. **Perimeter Calculation for Each Cell**:
   - Start with `p = 4` (maximum possible perimeter contribution)
   - Check all 4 adjacent cells (up, down, left, right)
   - For each adjacent cell that is land (not water), subtract 1 from `p`
   - Add the remaining `p` to total perimeter

4. **Boundary Handling**: 
   - Adjacent cells outside grid boundaries are treated as water
   - Only check cells within valid grid bounds

### Code Analysis:

```python
def bfs(r, c) -> int:
    q = deque([(r, c)])
    grid[r][c] = 2  # Mark as visited
    P = 0
    
    while q:
        r, c = q.popleft()
        p = 4  # Start with 4 potential perimeter sides
        
        # Check all 4 adjacent cells
        near = [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]
        for next_r, next_c in near:
            # If adjacent cell is within bounds and is land
            if (0 <= next_r < m and 0 <= next_c < n and 
                grid[next_r][next_c] != 0):
                p -= 1  # Reduce perimeter (shared border)
                
                # Add unvisited land cells to queue
                if grid[next_r][next_c] != 2:
                    q.append((next_r, next_c))
                    grid[next_r][next_c] = 2
        
        P += p  # Add this cell's perimeter contribution
    return P
```

### Time & Space Complexity:

- **Time Complexity**: O(m × n) where m and n are grid dimensions
  - Each cell is visited at most once during BFS
  - Grid traversal is O(m × n)

- **Space Complexity**: O(m × n) in worst case
  - Queue can contain up to all land cells
  - Grid modification uses O(1) extra space

### Alternative Approach:

A simpler approach without BFS would be to iterate through each cell once:

```python
def islandPerimeter(self, grid):
    perimeter = 0
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == 1:
                perimeter += 4
                # Check adjacent cells and subtract shared borders
                if i > 0 and grid[i-1][j] == 1: perimeter -= 1
                if j > 0 and grid[i][j-1] == 1: perimeter -= 1
                if i < len(grid)-1 and grid[i+1][j] == 1: perimeter -= 1
                if j < len(grid[0])-1 and grid[i][j+1] == 1: perimeter -= 1
    return perimeter
```

This alternative has the same time complexity but is simpler and doesn't modify the input grid.

# Tags

- **Data Structures**: 2D Array, Queue (for BFS)
- **Algorithms**: Breadth-First Search (BFS), Grid Traversal
- **Concepts**: Graph Theory, Connected Components, Perimeter Calculation
- **Difficulty**: Easy
- **Pattern**: Island Problems, Grid-based BFS

