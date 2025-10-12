## Problem

https://leetcode.com/problems/sudoku-solver/description/

```
Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

Each of the digits 1-9 must occur exactly once in each row.
Each of the digits 1-9 must occur exactly once in each column.
Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
The '.' character indicates empty cells.

Example 1:

Input: board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
Output: [["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]
Explanation: The input board is shown above and the only valid solution is shown below:

Constraints:

board.length == 9
board[i].length == 9
board[i][j] is a digit or '.'.
It is guaranteed that the input board has only one solution.
```

## Observations

1. **Problem Nature**: This is a classic constraint satisfaction problem that requires backtracking to find the unique solution.

2. **Sudoku Rules**: 
   - Each row must contain digits 1-9 exactly once
   - Each column must contain digits 1-9 exactly once  
   - Each 3x3 sub-box must contain digits 1-9 exactly once

3. **Key Insights**:
   - We need to track which numbers are already used in each row, column, and 3x3 box
   - For empty cells (marked with '.'), we try all possible values (1-9) and backtrack if invalid
   - The 3x3 box index can be calculated as: `(row // 3) * 3 + (col // 3)`

4. **Optimization Strategy**:
   - Use sets to store used numbers for O(1) lookup time
   - Convert string board to integer matrix for easier manipulation
   - Only try valid numbers (not already present in row/column/box)

## Solution

The solution uses **backtracking with constraint propagation**:

### Algorithm Steps:

1. **Initialization**:
   - Create sets to track used numbers in each row (`s_row`), column (`s_col`), and 3x3 box (`s_box`)
   - Convert string board to integer matrix for easier processing
   - Populate the tracking sets with existing numbers

2. **Backtracking Function (`dfs`)**:
   - **Base Cases**:
     - If `c == n`: Move to next row (`dfs(r+1, 0)`)
     - If `r == n`: All cells filled successfully, build final board and return `True`
   
   - **If cell is already filled**: Skip to next cell (`dfs(r, c+1)`)
   
   - **If cell is empty**: Try each digit 1-9:
     - Check if digit violates any constraint (row/column/box)
     - If valid: Place digit, update tracking sets, recurse
     - If recursion succeeds: Return `True`
     - If recursion fails: **Backtrack** (restore previous state)

3. **State Management**:
   - **Forward**: Add number to tracking sets and matrix
   - **Backtrack**: Remove number from tracking sets and reset matrix cell

### Time & Space Complexity:

- **Time Complexity**: O(9^(empty_cells)) in worst case, but pruning makes it much faster in practice
- **Space Complexity**: O(1) extra space (not counting recursion stack), since we use fixed-size tracking structures

## Tags

array, string, backtracking