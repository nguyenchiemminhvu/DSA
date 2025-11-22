## Problem

https://leetcode.com/problems/special-positions-in-a-binary-matrix/

```
Given an m x n binary matrix mat, return the number of special positions in mat.

A position (i, j) is called special if mat[i][j] == 1 and all other elements in row i and column j are 0 (rows and columns are 0-indexed).

Example 1:

Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
Output: 1
Explanation: (1, 2) is a special position because mat[1][2] == 1 and all other elements in row 1 and column 2 are 0.

Example 2:

Input: mat = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
Explanation: (0, 0), (1, 1) and (2, 2) are special positions.

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 100
mat[i][j] is either 0 or 1.
```

## Observations

1. **Special Position Definition**: A position (i, j) is special if:
   - mat[i][j] == 1 (the cell contains 1)
   - All other elements in row i are 0
   - All other elements in column j are 0

2. **Key Insight**: For a position to be special, the entire row must have exactly one 1, and the entire column must have exactly one 1.

3. **Optimization Opportunity**: Instead of checking each row and column for every potential special position, we can:
   - Pre-calculate the sum of each row
   - Pre-calculate the sum of each column
   - A position (i, j) is special if mat[i][j] == 1 AND row_sum[i] == 1 AND col_sum[j] == 1

## Solution

**Algorithm**: Two-pass approach with preprocessing

**Time Complexity**: O(m × n) where m is number of rows and n is number of columns
**Space Complexity**: O(m + n) for storing row and column sums

**Approach**:
1. **First Pass - Preprocessing**: Calculate the sum of 1s in each row and column
   - `srows[i]` stores the count of 1s in row i
   - `scols[j]` stores the count of 1s in column j

2. **Second Pass - Validation**: For each cell that contains 1:
   - Check if it's the only 1 in its row (srows[i] == 1)
   - Check if it's the only 1 in its column (scols[j] == 1)
   - If both conditions are met, increment the special positions count

**Why this works**:
- If srows[i] == 1, then row i has exactly one 1
- If scols[j] == 1, then column j has exactly one 1
- If mat[i][j] == 1 and both conditions above are true, then (i, j) is special

# Tags
Array, Matrix, Preprocessing

