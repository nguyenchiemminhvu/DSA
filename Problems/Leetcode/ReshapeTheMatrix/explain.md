## Problem

https://leetcode.com/problems/reshape-the-matrix/description/

```
In MATLAB, there is a handy function called reshape which can reshape an m x n matrix into a new one with a different size r x c keeping its original data.

You are given an m x n matrix mat and two integers r and c representing the number of rows and the number of columns of the wanted reshaped matrix.

The reshaped matrix should be filled with all the elements of the original matrix in the same row-traversing order as they were.

If the reshape operation with given parameters is possible and legal, output the new reshaped matrix; Otherwise, output the original matrix.

Example 1:

Input: mat = [[1,2],[3,4]], r = 1, c = 4
Output: [[1,2,3,4]]

Example 2:

Input: mat = [[1,2],[3,4]], r = 2, c = 4
Output: [[1,2],[3,4]]

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 100
-1000 <= mat[i][j] <= 1000
1 <= r, c <= 300
```

## Observations

1. **Problem Understanding**: We need to reshape a 2D matrix from dimensions `m×n` to `r×c` while preserving the order of elements when read row by row.

2. **Feasibility Check**: The total number of elements must remain the same, so `m×n` must equal `r×c`. If not, return the original matrix.

3. **Element Traversal**: Elements should be visited in row-major order (left to right, top to bottom) from the original matrix and placed in the same order in the new matrix.

4. **Index Mapping**: The key insight is converting 2D coordinates to a linear index and then back to 2D coordinates:
   - From 2D to linear: `index = i * n + j` (where `i`, `j` are coordinates in original matrix)
   - From linear to 2D: `new_i = index // c`, `new_j = index % c` (where `c` is columns in target matrix)

5. **Memory Efficiency**: We create a new matrix rather than trying to reshape in-place, which is simpler and clearer.

## Solution

**Algorithm Explanation:**

1. **Validation Phase**:
   - Get dimensions of original matrix: `m = len(mat)`, `n = len(mat[0])`
   - Check if reshape is possible: `m * n == r * c`
   - If not possible, return original matrix unchanged

2. **Initialization**:
   - Create new matrix `res` with dimensions `r×c` filled with zeros
   - `res = [[0] * c for _ in range(r)]`

3. **Element Transfer**:
   - Iterate through each element in original matrix using nested loops
   - For each element at position `(i,j)`:
     - Calculate linear index: `idx = i * n + j`
     - Map to new position: `(idx // c, idx % c)`
     - Copy element: `res[idx // c][idx % c] = mat[i][j]`

**Time Complexity**: O(m×n) - We visit each element exactly once
**Space Complexity**: O(r×c) - For the result matrix (excluding input)

**Key Insight**: The linear indexing approach elegantly handles the coordinate transformation. By treating the matrix as a flattened array temporarily, we can easily map positions between different matrix shapes.

**Example Walkthrough**:
- Input: `mat = [[1,2],[3,4]]`, `r=1`, `c=4`
- Original: 2×2, Target: 1×4
- Element mapping:
  - (0,0)→idx=0→(0,0): 1
  - (0,1)→idx=1→(0,1): 2  
  - (1,0)→idx=2→(0,2): 3
  - (1,1)→idx=3→(0,3): 4
- Result: `[[1,2,3,4]]`

# Tags

`Array` `Matrix` `Simulation` `Index-Mapping`

