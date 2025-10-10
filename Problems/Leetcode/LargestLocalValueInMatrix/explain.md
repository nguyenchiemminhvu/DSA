## Problem

https://leetcode.com/problems/largest-local-values-in-a-matrix/

```
You are given an n x n integer matrix grid.

Generate an integer matrix maxLocal of size (n - 2) x (n - 2) such that:

maxLocal[i][j] is equal to the largest value of the 3 x 3 matrix in grid centered around row i + 1 and column j + 1.
In other words, we want to find the largest value in every contiguous 3 x 3 matrix in grid.

Return the generated matrix.

Example 1:

Input: grid = [[9,9,8,1],[5,6,2,6],[8,2,6,4],[6,2,2,2]]
Output: [[9,9],[8,6]]
Explanation: The diagram above shows the original matrix and the generated matrix.
Notice that each value in the generated matrix corresponds to the largest value of a contiguous 3 x 3 matrix in grid.

Example 2:

Input: grid = [[1,1,1,1,1],[1,1,1,1,1],[1,1,2,1,1],[1,1,1,1,1],[1,1,1,1,1]]
Output: [[2,2,2],[2,2,2],[2,2,2]]
Explanation: Notice that the 2 is contained within every contiguous 3 x 3 matrix in grid.

Constraints:

n == grid.length == grid[i].length
3 <= n <= 100
1 <= grid[i][j] <= 100
```

## Observations

1. **Problem Structure**: We need to find the maximum value in every 3x3 submatrix of the given n×n grid.

2. **Output Size**: The result matrix will be of size (n-2)×(n-2) because:
   - We can only fit (n-2) 3×3 matrices horizontally 
   - We can only fit (n-2) 3×3 matrices vertically
   - The top-left corner of each 3×3 submatrix can be positioned from (0,0) to (n-3, n-3)

3. **3×3 Submatrix Pattern**: For each position (i,j) in the result matrix, we need to examine the 3×3 submatrix starting at position (i,j) in the original grid.

4. **In-place vs New Matrix**: The solution can either create a new result matrix or reuse the existing grid (which is what this solution does cleverly).

5. **Sliding Window Concept**: This is essentially a 2D sliding window problem where the window size is 3×3.

## Solution

The solution uses an **in-place approach** that's both memory-efficient and elegant:

### Algorithm Breakdown:

1. **Iterate through valid positions**: Loop through positions (i,j) where i,j ∈ [0, n-3], which are all valid top-left corners for 3×3 submatrices.

2. **Find maximum in each 3×3 submatrix**: 
   ```python
   grid[i][j] = max([grid[i + r][j + c] for r in range(0, 3) for c in range(0, 3)])
   ```
   - This list comprehension generates all 9 values in the 3×3 submatrix
   - `r` and `c` range from 0 to 2 (inclusive)
   - We store the maximum directly at position (i,j)

3. **Extract the result**: 
   ```python
   return [grid[i][0:n-2] for i in range(m-2)]
   ```
   - Take the first (n-2) rows
   - From each row, take the first (n-2) columns
   - This gives us exactly the (n-2)×(n-2) result matrix

### Key Insights:

- **In-place optimization**: Instead of creating a separate result matrix, we overwrite the original grid starting from the top-left corner.
- **No data corruption**: Since we process from top-left to bottom-right and only overwrite positions that won't be needed for future 3×3 submatrices, there's no data loss.
- **Memory efficiency**: Space complexity is O(1) extra space (not counting the input/output).

### Example Walkthrough:
For `grid = [[9,9,8,1],[5,6,2,6],[8,2,6,4],[6,2,2,2]]`:

1. Position (0,0): Max of 3×3 starting at (0,0) → Max{9,9,8,5,6,2,8,2,6} = 9
2. Position (0,1): Max of 3×3 starting at (0,1) → Max{9,8,1,6,2,6,2,6,4} = 9
3. Position (1,0): Max of 3×3 starting at (1,0) → Max{5,6,2,8,2,6,6,2,2} = 8
4. Position (1,1): Max of 3×3 starting at (1,1) → Max{6,2,6,2,6,4,2,2,2} = 6

Result: `[[9,9],[8,6]]`

### Time & Space Complexity:
- **Time**: O((n-2)² × 9) = O(n²) - we process (n-2)² positions, each requiring 9 comparisons
- **Space**: O(1) extra space (in-place modification)



## Tags

array