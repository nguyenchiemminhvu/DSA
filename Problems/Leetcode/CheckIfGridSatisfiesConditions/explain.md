## Problem

https://leetcode.com/problems/check-if-grid-satisfies-conditions/description/

```
You are given a 2D matrix grid of size m x n. You need to check if each cell grid[i][j] is:

1. Equal to the cell below it, i.e. grid[i][j] == grid[i + 1][j] (if it exists).
2. Different from the cell to its right, i.e. grid[i][j] != grid[i][j + 1] (if it exists).

Return true if all the cells satisfy these conditions, otherwise, return false.

Example 1:
Input: grid = [[1,0,2],[1,0,2]]
Output: true
Explanation: All the cells in the grid satisfy the conditions.

Example 2:
Input: grid = [[1,1,1],[0,0,0]]
Output: false
Explanation: All cells in the first row are equal.

Example 3:
Input: grid = [[1],[2],[3]]
Output: false
Explanation: Cells in the first column have different values.

Constraints:
- 1 <= n, m <= 10
- 0 <= grid[i][j] <= 9
```

## Observations

1. **Vertical Constraint**: Each cell must equal the cell directly below it (if exists)
   - This means all cells in the same column must have the same value
   - Therefore, each column is uniform from top to bottom

2. **Horizontal Constraint**: Each cell must differ from the cell to its right (if exists)
   - This means no two adjacent cells in the same row can be equal
   - Therefore, values must alternate or change across columns

3. **Key Insight**: Since all cells in a column are equal, we only need to check the first row
   - If condition 1 holds: all rows must be identical
   - If condition 2 holds: adjacent values in the first row must be different

4. **Simplified Problem**: 
   - Verify all rows are identical (satisfies vertical constraint)
   - Verify no adjacent elements in the first row are equal (satisfies horizontal constraint)

5. **Edge Cases**:
   - Single column: Only vertical constraint matters (always satisfied if m=1)
   - Single row: Only horizontal constraint matters
   - Single cell: Both constraints are vacuously true

## Solution

### Approach: Row Comparison with First Row Validation

The solution leverages the observation that vertical constraints force all rows to be identical.

**Algorithm**:
1. Extract the first row as a reference
2. Validate horizontal constraint on the first row (no adjacent duplicates)
3. Validate vertical constraint by comparing all rows to the first row

**Time Complexity**: O(m × n)
- Checking first row for adjacent duplicates: O(n)
- Comparing each of m rows with first row: O(m × n) in worst case
  - Python's list comparison is O(n) per row

**Space Complexity**: O(1)
- Only storing reference to first row (not copying)
- No additional data structures needed

**Why This Works**:
- If all rows equal `first_row`, then `grid[i][j] == grid[i+1][j]` for all valid i,j ✓
- If no adjacent elements in `first_row` are equal, then `grid[i][j] != grid[i][j+1]` for all valid i,j ✓
- Both conditions are necessary and sufficient

**Alternative Approach** (Direct Validation):
Check both conditions explicitly by iterating through all cells:
```python
def satisfiesConditions(self, grid: List[List[int]]) -> bool:
    m, n = len(grid), len(grid[0])
    
    for i in range(m):
        for j in range(n):
            # Check vertical constraint
            if i + 1 < m and grid[i][j] != grid[i + 1][j]:
                return False
            # Check horizontal constraint
            if j + 1 < n and grid[i][j] == grid[i][j + 1]:
                return False
    
    return True
```
This approach is also O(m × n) but performs more comparisons.

# Tags
#matrix #array #grid #validation #pattern-matching

