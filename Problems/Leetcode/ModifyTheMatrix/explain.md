## Problem

https://leetcode.com/problems/modify-the-matrix/description/

```
Given a 0-indexed m x n integer matrix matrix, create a new 0-indexed matrix called answer. Make answer equal to matrix, then replace each element with the value -1 with the maximum element in its respective column.

Return the matrix answer.

Example 1:

Input: matrix = [[1,2,-1],[4,-1,6],[7,8,9]]
Output: [[1,2,9],[4,8,6],[7,8,9]]
Explanation: The diagram above shows the elements that are changed (in blue).
- We replace the value in the cell [1][1] with the maximum value in the column 1, that is 8.
- We replace the value in the cell [0][2] with the maximum value in the column 2, that is 9.

Example 2:

Input: matrix = [[3,-1],[5,2]]
Output: [[3,2],[5,2]]
Explanation: The diagram above shows the elements that are changed (in blue).

Constraints:

m == matrix.length
n == matrix[i].length
2 <= m, n <= 50
-1 <= matrix[i][j] <= 100
The input is generated such that each column contains at least one non-negative integer.
```

## Observations

1. **Problem Pattern**: This is a matrix manipulation problem where we need to replace specific values (-1) with column-wise maximum values.

2. **Key Constraints**:
   - Matrix dimensions: 2 ≤ m, n ≤ 50 (small size, so efficiency isn't critical)
   - Values range: -1 ≤ matrix[i][j] ≤ 100
   - Each column is guaranteed to have at least one non-negative integer (ensuring we can always find a valid maximum)

3. **Approach Requirements**:
   - We need to find the maximum value in each column first
   - Then replace all -1 values with their respective column maximums
   - The solution can modify the input matrix in-place or create a new one

4. **Edge Cases**:
   - Columns with only one -1 and other positive values
   - Columns with multiple -1 values
   - No -1 values in the matrix (return as-is)

## Solution

**Algorithm**: Two-pass column-wise processing

**Step 1: Find Column Maximums**
```python
cols = [-1] * n  # Initialize with -1 (minimum possible value)
for c in range(n):
    for row in mat:
        cols[c] = max(cols[c], row[c])
```
- Create an array to store the maximum value for each column
- For each column, iterate through all rows to find the maximum value
- Since each column has at least one non-negative integer, the final maximum will be ≥ 0

**Step 2: Replace -1 Values**
```python
for i in range(m):
    for j in range(n):
        if mat[i][j] == -1:
            mat[i][j] = cols[j]
```
- Iterate through the entire matrix
- Replace any -1 with the corresponding column maximum from our precomputed array

**Time Complexity**: O(m × n) - We traverse the matrix twice
**Space Complexity**: O(n) - We store the maximum value for each column

**Why This Works**:
1. The two-pass approach ensures we have all column maximums before making replacements
2. We don't need to worry about replacing -1 values affecting our maximum calculations since we compute maximums first
3. The in-place modification is safe because we only change -1 values to positive values

**Alternative Approach**: We could solve this in one pass by scanning each column completely before moving to the next, but the two-pass approach is cleaner and easier to understand.

# Tags

