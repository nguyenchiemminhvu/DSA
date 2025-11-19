## Problem

https://leetcode.com/problems/minimum-operations-to-make-columns-strictly-increasing/description/

```
You are given a m x n matrix grid consisting of non-negative integers.

In one operation, you can increment the value of any grid[i][j] by 1.

Return the minimum number of operations needed to make all columns of grid strictly increasing.

Example 1:

Input: grid = [[3,2],[1,3],[3,4],[0,1]]

Output: 15

Explanation:

To make the 0th column strictly increasing, we can apply 3 operations on grid[1][0], 2 operations on grid[2][0], and 6 operations on grid[3][0].
To make the 1st column strictly increasing, we can apply 4 operations on grid[3][1].

Example 2:

Input: grid = [[3,2,1],[2,1,0],[1,2,3]]

Output: 12

Explanation:

To make the 0th column strictly increasing, we can apply 2 operations on grid[1][0], and 4 operations on grid[2][0].
To make the 1st column strictly increasing, we can apply 2 operations on grid[1][1], and 2 operations on grid[2][1].
To make the 2nd column strictly increasing, we can apply 2 operations on grid[1][2].

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
0 <= grid[i][j] < 2500
```

## Observations

1. **Goal**: Make all columns of the matrix strictly increasing from top to bottom
2. **Operation allowed**: Only increment operations (add 1 to any cell)
3. **Key insight**: Process the matrix row by row, column by column
4. **Greedy approach**: For each cell, if it's not greater than the cell above it, increment it to be exactly one more than the cell above
5. **Why greedy works**: Since we can only increment (never decrement), and we need strict increasing order, the minimum increment needed for any cell is to make it exactly `previous_cell + 1`
6. **Processing order**: Must process from top to bottom (row 1 to m-1) since each row depends on the values in the row above it
7. **Column independence**: Each column can be processed independently since operations on one column don't affect others

**Mathematical insight**: For any cell `grid[i][j]` where `grid[i][j] <= grid[i-1][j]`, the minimum operations needed is `(grid[i-1][j] - grid[i][j] + 1)` to make it `grid[i-1][j] + 1`.

## Solution

### Approach: Greedy Row-by-Row Processing

The solution uses a **greedy approach** that processes the matrix from top to bottom:

**Algorithm:**
1. **Initialize**: Start with operations count = 0
2. **Iterate**: For each row from 1 to m-1 (skip first row):
   - For each column j from 0 to n-1:
     - If `grid[i][j] <= grid[i-1][j]` (violates strictly increasing):
       - Calculate operations needed: `(grid[i-1][j] - grid[i][j] + 1)`
       - Add operations to total count
       - Update `grid[i][j] = grid[i-1][j] + 1`
3. **Return**: Total operations count

**Why this works:**
- **Greedy choice**: When a cell violates the strictly increasing property, the minimum increment needed is to make it exactly one more than the cell above
- **Optimal substructure**: The decision for each cell is independent and doesn't affect the optimality of decisions for other cells
- **No backtracking needed**: Since we can only increment, making the minimal required change at each step is always optimal

**Time Complexity**: O(m × n) - single pass through all matrix elements
**Space Complexity**: O(1) - only using constant extra space (modifying input in-place)

**Example walkthrough** with `grid = [[3,2],[1,3],[3,4],[0,1]]`:

```
Initial grid:
[3, 2]
[1, 3]  
[3, 4]
[0, 1]

Processing row 1:
- grid[1][0] = 1 <= grid[0][0] = 3 → operations += (3-1+1) = 3, grid[1][0] = 4
- grid[1][1] = 3 > grid[0][1] = 2 ✓

After row 1: operations = 3
[3, 2]
[4, 3]
[3, 4]
[0, 1]

Processing row 2:  
- grid[2][0] = 3 <= grid[1][0] = 4 → operations += (4-3+1) = 2, grid[2][0] = 5
- grid[2][1] = 4 > grid[1][1] = 3 ✓

After row 2: operations = 5  
[3, 2]
[4, 3]
[5, 4]
[0, 1]

Processing row 3:
- grid[3][0] = 0 <= grid[2][0] = 5 → operations += (5-0+1) = 6, grid[3][0] = 6  
- grid[3][1] = 1 <= grid[2][1] = 4 → operations += (4-1+1) = 4, grid[3][1] = 5

Final: operations = 15
```

**Alternative Implementation (without modifying input):**
```python
class Solution:
    def minimumOperations(self, grid: List[List[int]]) -> int:
        res = 0
        prev_row = grid[0][:]  # Copy first row
        
        for i in range(1, len(grid)):
            current_row = []
            for j in range(len(grid[0])):
                if grid[i][j] <= prev_row[j]:
                    needed = prev_row[j] + 1
                    res += needed - grid[i][j]
                    current_row.append(needed)
                else:
                    current_row.append(grid[i][j])
            prev_row = current_row
            
        return res
```

## Tags

array, matrix, greedy, simulation

