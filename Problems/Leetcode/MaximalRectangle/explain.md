## Problem

https://leetcode.com/problems/maximal-rectangle/description/

Given a `rows x cols` binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

**Example 1:**
```
Input: matrix = [["1","0","1","0","0"],
                 ["1","0","1","1","1"],
                 ["1","1","1","1","1"],
                 ["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the picture (middle-right area, 2x3 rectangle).
```

**Example 2:**
```
Input: matrix = [["0"]]
Output: 0
```

**Example 3:**
```
Input: matrix = [["1"]]
Output: 1
```

**Constraints:**
- `rows == matrix.length`
- `cols == matrix[i].length`
- `1 <= rows, cols <= 200`
- `matrix[i][j]` is '0' or '1'

## Observations

1. **Transform to Histogram Problem**: This problem can be reduced to the "Largest Rectangle in Histogram" problem by treating each row as a base of histograms.

2. **Height Array**: For each row, we maintain a height array where `height[c]` represents the number of consecutive 1's above (and including) the current row at column `c`.
   - If `matrix[r][c] == '1'`, increment `height[c]`
   - If `matrix[r][c] == '0'`, reset `height[c] = 0`

3. **Row-by-Row Processing**: Process each row sequentially:
   - Update the height array based on current row
   - Solve "Largest Rectangle in Histogram" for current height configuration
   - Track maximum area found

4. **Monotonic Stack Technique**: To efficiently find the largest rectangle in a histogram:
   - Find the nearest smaller height to the left for each bar
   - Find the nearest smaller height to the right for each bar
   - Calculate area: `height[i] * (right_boundary - left_boundary - 1)`

## Solution

### Approach: Dynamic Programming + Largest Rectangle in Histogram

**Core Idea**: Convert the 2D matrix problem into multiple 1D histogram problems.

**Algorithm**:

1. **Initialize**:
   - Create a `height` array of size `n` (number of columns), initialized to 0
   - This array tracks the height of consecutive 1's ending at the current row

2. **For each row in the matrix**:
   - Update the height array:
     - If `matrix[row][col] == '0'`: set `height[col] = 0` (break the consecutive 1's)
     - If `matrix[row][col] == '1'`: increment `height[col] += 1` (extend the bar)
   - Treat the current `height` array as a histogram
   - Calculate the largest rectangle area in this histogram
   - Update the maximum area

3. **Largest Rectangle in Histogram** (helper function):
   - Use two monotonic stacks to find boundaries:
     - **Left pass**: Find nearest smaller element to the left (stores in `s_left`)
     - **Right pass**: Find nearest smaller element to the right (stores in `s_right`)
   - For each position `i`:
     - Width = `s_right[i] - s_left[i] - 1`
     - Area = `heights[i] * width`
   - Return maximum area

**Visualization Example**:
```
Matrix:           Row 0 Heights:    Row 1 Heights:    Row 2 Heights:    Row 3 Heights:
["1","0","1","0","0"]   [1,0,1,0,0]      [2,0,2,1,1]      [3,1,3,2,2]      [4,0,0,3,0]
["1","0","1","1","1"]
["1","1","1","1","1"]
["1","0","0","1","0"]

For Row 2, heights = [3,1,3,2,2]
Largest rectangle in this histogram = 6 (height=2, width=3, columns 2-4)
```

**Time Complexity**: $O(m \times n)$
- Process each row: $O(m)$
- For each row, calculate largest rectangle: $O(n)$
- Total: $O(m \times n)$

**Space Complexity**: $O(n)$
- Height array: $O(n)$
- Monotonic stacks in helper function: $O(n)$

**Key Insights**:
- The problem leverages the fact that any maximal rectangle must have its bottom edge at some row
- By converting each row into a histogram, we ensure we check all possible bottom edges
- Monotonic stack allows us to efficiently find the widest rectangle for each bar height

# Tags
`Dynamic Programming`, `Stack`, `Monotonic Stack`, `Matrix`, `Histogram`, `Array`

