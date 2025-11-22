## Problem

https://leetcode.com/problems/surface-area-of-3d-shapes/

```
You are given an n x n grid where you have placed some 1 x 1 x 1 cubes. Each value v = grid[i][j] represents a tower of v cubes placed on top of cell (i, j).

After placing these cubes, you have decided to glue any directly adjacent cubes to each other, forming several irregular 3D shapes.

Return the total surface area of the resulting shapes.

Note: The bottom face of each shape counts toward its surface area.

Example 1:

Input: grid = [[1,2],[3,4]]
Output: 34

Example 2:

Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
Output: 32

Example 3:

Input: grid = [[2,2,2],[2,1,2],[2,2,2]]
Output: 46

Constraints:

n == grid.length == grid[i].length
1 <= n <= 50
0 <= grid[i][j] <= 50
```

## Observations

1. **Understanding the Problem:**
   - We have an n×n grid where each cell contains a tower of cubes
   - `grid[i][j] = v` means there are `v` cubes stacked vertically at position (i,j)
   - Adjacent cubes are glued together, so we need to calculate the total surface area
   - The bottom face of each shape counts toward the surface area

2. **Key Insights:**
   - Each cube has 6 faces initially
   - When cubes are adjacent (touching), the touching faces don't contribute to surface area
   - Two types of adjacency to consider:
     - **Vertical adjacency**: Cubes in the same tower (stacked on top of each other)
     - **Horizontal adjacency**: Cubes in neighboring grid cells (north, south, east, west)

3. **Surface Area Calculation Strategy:**
   - Start with total surface area if all cubes were isolated: `total_cubes × 6`
   - Subtract the internal faces that are hidden due to adjacency
   - For vertical stacking: if there are `v` cubes in a tower, there are `(v-1)` internal connections, each hiding 2 faces
   - For horizontal adjacency: between two neighboring towers with heights `h1` and `h2`, there are `min(h1, h2)` connections, each hiding 2 faces

## Solution

1. **Calculate Initial Surface Area:**
   ```python
   res = sum([sum(row) for row in grid]) * 6
   ```
   - Count total number of cubes in the entire grid
   - Multiply by 6 since each cube has 6 faces
   - This assumes all cubes are isolated (no touching faces)

2. **Subtract Vertical Internal Faces:**
   ```python
   for row in grid:
       for val in row:
           if val > 0:
               res -= (val - 1) * 2
   ```
   - For each tower with `val` cubes, there are `(val-1)` internal connections
   - Each internal connection hides 2 faces (top of lower cube + bottom of upper cube)
   - Only process towers with at least 1 cube (`val > 0`)

3. **Subtract Horizontal Internal Faces:**
   ```python
   for i in range(n):
       for j in range(n):
           if i > 0:
               res -= min(grid[i][j], grid[i - 1][j]) * 2
           if j > 0:
               res -= min(grid[i][j], grid[i][j - 1]) * 2
   ```
   - Check adjacency with north neighbor (`i > 0`) and west neighbor (`j > 0`)
   - Between two towers of heights `h1` and `h2`, the number of touching cube pairs is `min(h1, h2)`
   - Each touching pair hides 2 faces
   - We only check north and west to avoid double-counting (each pair is counted once)

**Time Complexity:** O(n²) - We iterate through the grid multiple times
**Space Complexity:** O(1) - Only using constant extra space

**Example Walkthrough with `grid = [[1,2],[3,4]]`:**
- Initial surface area: (1+2+3+4) × 6 = 60
- Vertical subtractions: (1-1)×2 + (2-1)×2 + (3-1)×2 + (4-1)×2 = 0 + 2 + 4 + 6 = 12
- Horizontal subtractions: 
  - (1,0) with (0,0): min(3,1)×2 = 2
  - (1,1) with (0,1): min(4,2)×2 = 4  
  - (0,1) with (0,0): min(2,1)×2 = 2
  - (1,1) with (1,0): min(4,3)×2 = 6
- Total: 60 - 12 - (2+4+2+6) = 60 - 12 - 14 = 34 ✓

# Tags
#geometry #3d #array #math #simulation

