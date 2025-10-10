## Problem Description

https://leetcode.com/problems/valid-sudoku/description/

```
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.

Example 1:

Input: board = 
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: true

Example 2:

Input: board = 
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.

Constraints:

board.length == 9
board[i].length == 9
board[i][j] is a digit 1-9 or '.'.
```

## Observations

1. **Rows, Columns, and Boxes**  
- We need to check three things: every row, every column, and every 3x3 box.
- If any digit appears more than once in any of these, the board is invalid.

1. **Counting Digits**  
- For each row, column, or box, we can count how many times each digit appears.
- If any digit appears more than once, return `False`.

1. **Ignoring Empty Cells**  
- We only care about cells with digits (`1` to `9`).  
- Cells with `.` are skipped.

### Steps

1. **Check Rows**  
- For each row, count the digits.
- If any digit appears more than once, return `False`.

1. **Check Columns**  
- For each column, count the digits.
- If any digit appears more than once, return `False`.

1. **Check 3x3 Boxes**  
- For each 3x3 box, count the digits.
- If any digit appears more than once, return `False`.

1. **Return True**  
- If all checks pass, the board is valid.

## Tags

array, hash table