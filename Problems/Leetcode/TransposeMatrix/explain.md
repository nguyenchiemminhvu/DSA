## Problem

https://leetcode.com/problems/transpose-matrix/description/

```
Given a 2D integer array matrix, return the transpose of matrix.

The transpose of a matrix is the matrix flipped over its main diagonal, switching the matrix's row and column indices.

Example 1:

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[1,4,7],[2,5,8],[3,6,9]]

Example 2:

Input: matrix = [[1,2,3],[4,5,6]]
Output: [[1,4],[2,5],[3,6]]

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 1000
1 <= m * n <= 105
-109 <= matrix[i][j] <= 109
```

## Observations

1. **Matrix Transpose Definition**: The transpose of a matrix swaps rows and columns - element at position `(i, j)` in the original matrix becomes element at position `(j, i)` in the transposed matrix.

2. **Dimension Changes**: If the original matrix has dimensions `m × n`, the transposed matrix will have dimensions `n × m`.

3. **Visual Example**:
   ```
   Original (3×3):     Transposed (3×3):
   [1, 2, 3]          [1, 4, 7]
   [4, 5, 6]    =>    [2, 5, 8]
   [7, 8, 9]          [3, 6, 9]
   ```

4. **Non-square matrices**: The algorithm works for both square and rectangular matrices.

5. **Initialize dimensions**: Get `m` (rows) and `n` (columns) from the input matrix.

6. **Create result matrix**: Initialize a new matrix with dimensions `n × m` (swapped dimensions).

7. **Copy with swapped indices**: For each element at position `(i, j)` in the original matrix, place it at position `(j, i)` in the result matrix.

**Time Complexity**: O(m × n) - We visit each element exactly once.

**Space Complexity**: O(m × n) - We create a new matrix to store the result.

**Key Insight**: The core operation is the index swap: `res[j][i] = mat[i][j]`. This single line performs the transpose operation by mapping each element from its original position to its transposed position.

# Tags

- Array
- Matrix
- Simulation

