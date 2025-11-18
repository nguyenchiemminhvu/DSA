## Problem

https://leetcode.com/problems/projection-area-of-3d-shapes/description/

```
You are given an n x n grid where we place some 1 x 1 x 1 cubes that are axis-aligned with the x, y, and z axes.

Each value v = grid[i][j] represents a tower of v cubes placed on top of the cell (i, j).

We view the projection of these cubes onto the xy, yz, and zx planes.

A projection is like a shadow, that maps our 3-dimensional figure to a 2-dimensional plane. We are viewing the "shadow" when looking at the cubes from the top, the front, and the side.

Return the total area of all three projections.

Example 1:

Input: grid = [[1,2],[3,4]]
Output: 17
Explanation: Here are the three projections ("shadows") of the shape made with each axis-aligned plane.

Example 2:

Input: grid = [[2]]
Output: 5

Example 3:

Input: grid = [[1,0],[0,2]]
Output: 8

Constraints:

n == grid.length == grid[i].length
1 <= n <= 50
0 <= grid[i][j] <= 50
```

## Observations

This problem is about calculating the projection areas of 3D shapes onto three different planes:

1. **XY Plane (Top View)**: Looking down from above
   - Each cell with height > 0 contributes exactly 1 unit of area
   - The projection area is simply the count of non-zero cells
   - Example: `[[1,2],[3,4]]` → 4 cells are non-zero → area = 4

2. **YZ Plane (Side View - looking from X direction)**: Looking from the side
   - For each row, only the tallest tower matters (shadows everything behind it)
   - The projection area is the sum of maximum heights of each row
   - Example: `[[1,2],[3,4]]` → max(1,2) + max(3,4) = 2 + 4 = 6

3. **ZX Plane (Side View - looking from Y direction)**: Looking from another side
   - For each column, only the tallest tower matters
   - The projection area is the sum of maximum heights of each column
   - Example: `[[1,2],[3,4]]` → max(1,3) + max(2,4) = 3 + 4 = 7

**Key Insights:**
- The total projection area is the sum of all three individual projection areas
- Each projection captures different aspects of the 3D structure
- XY projection counts "footprint", YZ and ZX projections capture "silhouettes"

## Solution

The solution calculates each projection area separately and sums them up:

### Step 1: XY Plane Projection (Top View)
```python
for row in grid:
    res += sum(1 for val in row if val > 0)
```
- Count all non-zero cells in the grid
- Each non-zero cell contributes 1 unit of area when viewed from above

### Step 2: YZ Plane Projection (Side View - Row-wise)
```python
for row in grid:
    res += max(row)
```
- For each row, find the maximum height
- The tallest tower in each row determines the projection height for that row

### Step 3: ZX Plane Projection (Side View - Column-wise)
```python
for i in range(n):
    max_col = 0
    for row in grid:
        max_col = max(max_col, row[i])
    res += max_col
```
- For each column, find the maximum height across all rows
- The tallest tower in each column determines the projection height for that column

### Example Walkthrough
For `grid = [[1,2],[3,4]]`:

1. **XY Projection**: All 4 cells are non-zero → area = 4
2. **YZ Projection**: max(1,2) + max(3,4) = 2 + 4 = 6  
3. **ZX Projection**: max(1,3) + max(2,4) = 3 + 4 = 7
4. **Total**: 4 + 6 + 7 = 17

**Time Complexity**: O(n²) - We iterate through the grid multiple times
**Space Complexity**: O(1) - Only using constant extra space

## Tags

array, math, geometry, simulation

