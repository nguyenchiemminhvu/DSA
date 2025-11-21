## Problem

https://leetcode.com/problems/flip-square-submatrix-vertically/description/

```
You are given an m x n integer matrix grid, and three integers x, y, and k.

The integers x and y represent the row and column indices of the top-left corner of a square submatrix and the integer k represents the size (side length) of the square submatrix.

Your task is to flip the submatrix by reversing the order of its rows vertically.

Return the updated matrix.

Example 1:

Input: grid = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]], x = 1, y = 0, k = 3

Output: [[1,2,3,4],[13,14,15,8],[9,10,11,12],[5,6,7,16]]

Explanation:

The diagram above shows the grid before and after the transformation.

Example 2:

Input: grid = [[3,4,2,3],[2,3,4,2]], x = 0, y = 2, k = 2

Output: [[3,4,4,2],[2,3,2,3]]

Explanation:

The diagram above shows the grid before and after the transformation.

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
1 <= grid[i][j] <= 100
0 <= x < m
0 <= y < n
1 <= k <= min(m - x, n - y)
```

## Observations

1. **Problem Understanding**: We need to flip a k×k square submatrix vertically (reverse row order) within a larger m×n grid. The submatrix starts at position (x, y) and has side length k.

2. **Vertical Flip Definition**: "Flipping vertically" means reversing the order of rows within the submatrix:
   - The top row becomes the bottom row
   - The second row becomes the second-to-last row
   - And so on...
   - This is equivalent to reflecting the submatrix across its horizontal center line

3. **Submatrix Boundaries**: 
   - Top-left corner: (x, y)
   - Bottom-right corner: (x + k - 1, y + k - 1)
   - The submatrix spans from row x to row (x + k - 1) and column y to column (y + k - 1)

4. **Column-by-Column Processing**: Since we're flipping rows, we can process each column independently within the submatrix. For each column c in range [y, y + k), we reverse the elements in rows [x, x + k).

5. **Two-Pointer Swapping Pattern**: For each column in the submatrix, we use two pointers:
   - `u` (up): starts at row x (top of submatrix)
   - `d` (down): starts at row (x + k - 1) (bottom of submatrix)
   - We swap elements and move pointers toward the center until they meet

6. **In-Place Modification**: The algorithm modifies the grid in-place, which is memory efficient and matches the problem requirement to return the updated matrix.

7. **Example Walkthrough**:
   ```
   Original: [[1,2,3,4],     After flip (x=1, y=0, k=3):
             [5,6,7,8],   →                [[1,2,3,4],
             [9,10,11,12],                  [13,14,15,8],
             [13,14,15,16]]                 [9,10,11,12],
                                           [5,6,7,16]]
   ```
   - The 3×3 submatrix starting at (1,0) gets flipped
   - Rows within the submatrix: [5,6,7] ↔ [13,14,15], [9,10,11] stays in middle

## Solution

The solution implements a **column-by-column vertical flip** using the two-pointer technique:

### Algorithm Breakdown:

1. **Calculate submatrix bounds**:
   ```python
   xx, yy = x + k, y + k
   ```
   - `xx` = first row after the submatrix (x + k)
   - `yy` = first column after the submatrix (y + k)

2. **Process each column in the submatrix**:
   ```python
   for c in range(y, yy):
   ```
   - Iterate through columns from y to (y + k - 1)

3. **Set up two pointers for each column**:
   ```python
   u = x          # Top pointer (starts at first row of submatrix)
   d = xx - 1     # Bottom pointer (starts at last row of submatrix)
   ```

4. **Swap elements while pointers don't cross**:
   ```python
   while u <= d:
       grid[u][c], grid[d][c] = grid[d][c], grid[u][c]
       u += 1
       d -= 1
   ```
   - Swap elements at positions (u, c) and (d, c)
   - Move pointers toward the center
   - Continue until pointers meet or cross

### Key Insights:

- **Column Independence**: Each column can be processed independently since we're only swapping within rows
- **Two-Pointer Efficiency**: The two-pointer approach ensures each element is swapped exactly once
- **Boundary Safety**: The constraint `k <= min(m - x, n - y)` ensures the submatrix fits within the grid
- **In-Place Operation**: No extra space needed beyond the input grid

### Time & Space Complexity:

- **Time Complexity**: O(k²) - We process k columns, each with k/2 swaps on average
- **Space Complexity**: O(1) - Only using constant extra space for variables

### Example Trace:
For `grid = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]`, `x=1, y=0, k=3`:

- Column 0: Swap (1,0)↔(3,0) → 5↔13, then (2,0)↔(2,0) → 9 stays
- Column 1: Swap (1,1)↔(3,1) → 6↔14, then (2,1)↔(2,1) → 10 stays  
- Column 2: Swap (1,2)↔(3,2) → 7↔15, then (2,2)↔(2,2) → 11 stays

Result: The 3×3 submatrix rows are vertically flipped while the rest of the grid remains unchanged.

# Tags

`Array` `Matrix` `Two Pointers` `In-Place Algorithm` `Submatrix Manipulation`

