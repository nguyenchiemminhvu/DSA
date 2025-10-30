## Problem

https://leetcode.com/problems/largest-submatrix-with-rearrangements/

```
You are given a binary matrix matrix of size m x n, and you are allowed to rearrange the columns of the matrix in any order.

Return the area of the largest submatrix within matrix where every element of the submatrix is 1 after reordering the columns optimally.

Example 1:

Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
Output: 4
Explanation: You can rearrange the columns as shown above.
The largest submatrix of 1s, in bold, has an area of 4.

Example 2:

Input: matrix = [[1,0,1,0,1]]
Output: 3
Explanation: You can rearrange the columns as shown above.
The largest submatrix of 1s, in bold, has an area of 3.

Example 3:

Input: matrix = [[1,1,0],[1,0,1]]
Output: 2
Explanation: Notice that you must rearrange entire columns, and there is no way to make a submatrix of 1s larger than an area of 2.

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m * n <= 105
matrix[i][j] is either 0 or 1.
```

## Observations

1. **Column Rearrangement Freedom**: We can rearrange entire columns in any order, which is the key insight. We cannot rearrange individual elements within rows, only entire columns.

2. **Consecutive 1s Matter**: For any valid submatrix of 1s, we need consecutive 1s in each column. The height of such a submatrix in any column is limited by the number of consecutive 1s ending at that row.

3. **Transform to Height Problem**: We can convert this into a "largest rectangle in histogram" type problem by:
   - Converting each cell to represent the height of consecutive 1s ending at that position
   - For each row, we get a histogram where each column represents a height
   - We need to find the largest rectangle area in this histogram

4. **Greedy Column Selection**: After transforming to heights, for each row we want to pick the tallest available columns (heights) and arrange them optimally to maximize area.

5. **Area Calculation Pattern**: For a row with heights sorted in descending order `[h1, h2, h3, ...]`:
   - Using only the tallest column: area = h1 × 1
   - Using the 2 tallest columns: area = h2 × 2 (limited by the shorter height)
   - Using the 3 tallest columns: area = h3 × 3
   - And so on...

## Solution

The solution uses a two-phase approach:

### Phase 1: Convert to Heights
```python
for c in range(n):
    count = 0
    for r in range(m):
        if mat[r][c] == 1:
            count += 1
            mat[r][c] = count  # Height of consecutive 1s ending here
        else:
            count = 0          # Reset height to 0
```

- **Purpose**: Transform each cell to represent the height of consecutive 1s ending at that position
- **Example**: 
  ```
  [[0,0,1],     [[0,0,1],
   [1,1,1],  →   [1,1,2],
   [1,0,1]]      [2,0,3]]
  ```

### Phase 2: Find Maximum Rectangle for Each Row
```python
new_mat = [sorted(row, reverse=True) for row in mat]
res = 0
for row in new_mat:
    horizontal = 1
    for height in row:
        res = max(res, height * horizontal)
        horizontal += 1
```

- **Sorting**: For each row, sort heights in descending order to optimally arrange columns
- **Greedy Selection**: For each position in the sorted row, calculate the area using that height as the limiting factor
- **Area Formula**: `height × width` where width is the number of columns we're considering (including this one)

### Example Walkthrough

Original matrix:
```
[[0,0,1],
 [1,1,1],
 [1,0,1]]
```

After Phase 1 (heights):
```
[[0,0,1],  ← Row 0: heights = [0,0,1]
 [1,1,2],  ← Row 1: heights = [1,1,2] 
 [2,0,3]]  ← Row 2: heights = [2,0,3]
```

After sorting each row (Phase 2):
```
[[1,0,0],  ← Sorted: [1,0,0] → max area = max(1×1, 0×2, 0×3) = 1
 [2,1,1],  ← Sorted: [2,1,1] → max area = max(2×1, 1×2, 1×3) = 3  
 [3,2,0]]  ← Sorted: [3,2,0] → max area = max(3×1, 2×2, 0×3) = 4
```

The maximum area across all rows is **4**.

### Why This Works

1. **Column Rearrangement**: By sorting each row, we optimally rearrange columns to maximize the rectangle area for that specific row level.

2. **Height-Limited Rectangles**: At each row, the rectangle height is limited by the shortest column in our selection. By processing from tallest to shortest heights, we ensure we're always making the optimal choice.

3. **Comprehensive Coverage**: We consider every possible row as a potential bottom boundary of our rectangle, ensuring we don't miss the optimal solution.

## Tags

array, greedy