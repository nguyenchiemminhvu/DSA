## Problem

https://leetcode.com/problems/image-smoother/description/

```
An image smoother is a filter of the size 3 x 3 that can be applied to each cell of an image by rounding down the average of the cell and the eight surrounding cells (i.e., the average of the nine cells in the blue smoother). If one or more of the surrounding cells of a cell is not present, we do not consider it in the average (i.e., the average of the four cells in the red smoother).

Given an m x n integer matrix img representing the grayscale of an image, return the image after applying the smoother on each cell of it.

Example 1:

Input: img = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[0,0,0],[0,0,0],[0,0,0]]
Explanation:
For the points (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
For the points (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
For the point (1,1): floor(8/9) = floor(0.88888889) = 0

Example 2:

Input: img = [[100,200,100],[200,50,200],[100,200,100]]
Output: [[137,141,137],[141,138,141],[137,141,137]]
Explanation:
For the points (0,0), (0,2), (2,0), (2,2): floor((100+200+200+50)/4) = floor(137.5) = 137
For the points (0,1), (1,0), (1,2), (2,1): floor((200+200+50+200+100+100)/6) = floor(141.666667) = 141
For the point (1,1): floor((50+200+200+200+200+100+100+100+100)/9) = floor(138.888889) = 138

Constraints:

m == img.length
n == img[i].length
1 <= m, n <= 200
0 <= img[i][j] <= 255
```

## Observations

1. **3x3 Filter Pattern**: For each cell at position (i, j), we need to consider a 3x3 grid centered on that cell:
   ```
   (i-1,j-1) (i-1,j) (i-1,j+1)
   (i,j-1)   (i,j)   (i,j+1)
   (i+1,j-1) (i+1,j) (i+1,j+1)
   ```

2. **Boundary Handling**: Cells near the edges/corners of the matrix will have fewer valid neighbors:
   - Corner cells: 4 valid cells (including itself)
   - Edge cells: 6 valid cells (including itself)  
   - Interior cells: 9 valid cells (including itself)

3. **Floor Operation**: We need to floor the average, not round it. This means we always round down to the nearest integer.

4. **Independent Calculations**: Each cell's smoothed value depends only on the original matrix values, so we need to create a new result matrix rather than modifying in-place.

## Solution

**Approach: Brute Force with Boundary Checking**

The solution uses a straightforward approach:

1. **Helper Function**: `get_smoother_idx(r, c)` generates all 9 possible neighbor coordinates for a 3x3 grid centered at (r, c).

2. **Boundary Validation**: For each cell, we iterate through the 9 potential neighbors and only include those that are within matrix bounds (`0 <= r < m and 0 <= c < n`).

3. **Average Calculation**: We sum all valid neighbor values and count how many valid neighbors we found, then compute `floor(sum / count)`.

4. **Result Construction**: We build a new matrix with the smoothed values.

**Time Complexity**: O(m × n × 9) = O(m × n) since we check at most 9 neighbors for each cell.

**Space Complexity**: O(m × n) for the result matrix.

**Key Implementation Details**:
- The helper function returns all 9 coordinates systematically (top row, middle row, bottom row)
- We use separate `s` (sum) and `count` variables to track valid neighbors
- The `floor()` function ensures we round down as required
- We create a new grid to avoid modifying the original during calculation

# Tags

array