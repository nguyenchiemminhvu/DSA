## Problem

https://leetcode.com/problems/set-matrix-zeroes/description

Given an m x n integer matrix, if an element is 0, set its entire row and column to 0's in-place.

**Constraints:**
- m == matrix.length
- n == matrix[0].length
- 1 <= m, n <= 200
- -2³¹ <= matrix[i][j] <= 2³¹ - 1

**Examples:**

Example 1:
```
Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]
```

Example 2:
```
Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
```

**Follow-up:**
- A straightforward solution using O(mn) space is probably a bad idea.
- A simple improvement uses O(m + n) space, but still not the best solution.
- Could you devise a constant space solution?

## Observations

1. **Naive Approach (O(mn) space)**: Create a copy of the matrix and mark zeros in the original - violates in-place requirement.

2. **Mask Arrays Approach (O(m + n) space)**: Use two boolean arrays to track which rows and columns contain zeros:
   - First pass: identify all zero positions and mark their rows and columns
   - Second pass: set elements to zero based on mask arrays
   - This avoids accidentally processing newly set zeros

3. **Key Insight for In-Place Solution**: Use the first row and first column as storage for row/column information:
   - Use `matrix[0][j]` to indicate if column j should be zeroed
   - Use `matrix[i][0]` to indicate if row i should be zeroed
   - Handle first row and first column separately to avoid overwriting their markers
   - Use two flags to track if first row/column themselves need to be zeroed

## Solution

### Approach 1: Mask Arrays (O(m + n) Space)

```python
class Solution:
    def setZeroes(self, mat: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        m, n = len(mat), len(mat[0])
        mask_row = [False] * m
        mask_col = [False] * n
        
        # First pass: identify rows and columns with zeros
        for i in range(m):
            for j in range(n):
                if mat[i][j] == 0:
                    mask_row[i] = True
                    mask_col[j] = True
        
        # Second pass: set elements to zero based on masks
        for i in range(m):
            for j in range(n):
                if mask_row[i] or mask_col[j]:
                    mat[i][j] = 0
```

**Time Complexity:** O(m × n) - two passes through the matrix
**Space Complexity:** O(m + n) - for row and column mask arrays

**Explanation:**
- We use separate boolean arrays to track which rows and columns should be zeroed
- In the first pass, we scan the entire matrix and mark rows/columns that contain 0
- In the second pass, we set elements to 0 if their row or column is marked
- This two-pass approach avoids the issue of accidentally processing newly set zeros

### Approach 2: In-Place with O(1) Space

```python
class Solution:
    def setZeroes(self, mat: List[List[int]]) -> None:
        m, n = len(mat), len(mat[0])
        first_row_zero = False
        first_col_zero = False
        
        # Check if first row/column need to be zeroed
        for j in range(n):
            if mat[0][j] == 0:
                first_row_zero = True
                break
        
        for i in range(m):
            if mat[i][0] == 0:
                first_col_zero = True
                break
        
        # Use first row/column as markers
        for i in range(1, m):
            for j in range(1, n):
                if mat[i][j] == 0:
                    mat[i][0] = 0
                    mat[0][j] = 0
        
        # Set zeros based on markers
        for i in range(1, m):
            for j in range(1, n):
                if mat[i][0] == 0 or mat[0][j] == 0:
                    mat[i][j] = 0
        
        # Handle first row
        if first_row_zero:
            for j in range(n):
                mat[0][j] = 0
        
        # Handle first column
        if first_col_zero:
            for i in range(m):
                mat[i][0] = 0
```

**Time Complexity:** O(m × n) - multiple passes through the matrix
**Space Complexity:** O(1) - only two boolean flags

**Explanation:**
- Store row/column zero information in the first row and column of the matrix itself
- First, check if the first row or first column originally contained zeros (store in flags)
- Then, use `matrix[0][j]` to mark if column j should be zeroed and `matrix[i][0]` for rows
- Finally, apply the markers to set elements to zero, handling first row/column separately based on saved flags

# Tags

#array #matrix #in-place #two-pass #marking

