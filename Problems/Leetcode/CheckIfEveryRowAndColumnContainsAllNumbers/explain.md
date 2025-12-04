## Problem

https://leetcode.com/problems/check-if-every-row-and-column-contains-all-numbers/description/

```
An n x n matrix is valid if every row and every column contains all the integers from 1 to n (inclusive).

Given an n x n integer matrix matrix, return true if the matrix is valid. Otherwise, return false.

Example 1:
Input: matrix = [[1,2,3],[3,1,2],[2,3,1]]
Output: true
Explanation: In this case, n = 3, and every row and column contains the numbers 1, 2, and 3.
Hence, we return true.

Example 2:
Input: matrix = [[1,1,1],[1,2,3],[1,2,3]]
Output: false
Explanation: In this case, n = 3, but the first row and the first column do not contain the numbers 2 or 3.
Hence, we return false.

Constraints:
- n == matrix.length == matrix[i].length
- 1 <= n <= 100
- 1 <= matrix[i][j] <= n
```

## Observations

1. **Matrix Properties**: The problem asks us to validate an n x n matrix where each row and column must contain all integers from 1 to n exactly once (similar to Sudoku constraints).

2. **Set-Based Validation**: Since each row/column must contain all numbers from 1 to n with no duplicates, we can use a set to check if the row/column contains exactly the expected numbers.

3. **Two-Phase Validation**:
   - First, validate all rows
   - Then, validate all columns
   - If any row or column fails validation, the entire matrix is invalid

4. **Early Termination**: We can return `false` as soon as we find any row or column that doesn't contain all numbers from 1 to n.

5. **Space Optimization**: We can create a reference set `{1, 2, 3, ..., n}` once and compare each row/column against it.

## Solution

### Approach: Set Comparison

**Algorithm:**

1. **Initialize Reference Set**: Create a set containing all integers from 1 to n. This will be our reference for comparison.

2. **Validate Rows**: 
   - Iterate through each row in the matrix
   - Convert the row to a set
   - Compare with the reference set
   - If any row doesn't match, return `false`

3. **Validate Columns**:
   - Iterate through each column index (0 to n-1)
   - For each column, collect all elements from that column into a set
   - Compare with the reference set
   - If any column doesn't match, return `false`

4. **Return Result**: If all rows and columns pass validation, return `true`

**Complexity Analysis:**

- **Time Complexity**: O(n²)
  - Creating the reference set: O(n)
  - Checking all rows: O(n²) - iterating through n rows, each with n elements
  - Checking all columns: O(n²) - for each of n columns, iterate through n rows
  - Overall: O(n²)

- **Space Complexity**: O(n)
  - Reference set: O(n)
  - Temporary set for each row/column: O(n)
  - Overall: O(n)

**Key Insights:**

1. **Set Properties**: Using sets automatically handles duplicate detection and allows for O(1) comparison when sets are equal in size.

2. **Column Traversal**: To check columns, we iterate through column indices and collect elements vertically by accessing `row[i]` for each row.

3. **Clean Validation**: By comparing sets directly with `!=`, we simultaneously check:
   - All expected numbers are present
   - No duplicates exist
   - No invalid numbers exist

4. **Alternative Optimization**: For very large matrices, we could combine row and column checks in a single pass, but this adds complexity without significant benefit for the given constraints (n ≤ 100).

# Tags

