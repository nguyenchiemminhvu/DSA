## Problem

https://leetcode.com/problems/n-queens/

```
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

Example 1:

Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above

Example 2:

Input: n = 1
Output: [["Q"]]

Constraints:

1 <= n <= 9
```

## Observations

1. **Queen Attack Patterns**: A queen can attack horizontally, vertically, and diagonally. This means two queens cannot be:
   - In the same row
   - In the same column  
   - On the same diagonal (both main diagonal and anti-diagonal)

2. **Diagonal Constraints**: 
   - Main diagonal: cells where `row + col` is constant
   - Anti-diagonal: cells where `row - col` is constant
   - These mathematical relationships help us track diagonal conflicts efficiently

3. **Search Space**: For an n×n board, we need to place exactly n queens, one in each row. This reduces the problem from placing n queens anywhere to choosing one column for each row.

4. **Backtracking Nature**: We can use DFS with backtracking - try placing a queen, recursively solve for remaining rows, and backtrack if no solution exists.

5. **Conflict Detection**: Using sets to track occupied rows, columns, and diagonals allows O(1) conflict checking instead of scanning the entire board.

## Solution

**Data Structures Used:**
- `s_row`, `s_col`: Sets to track occupied rows and columns
- `s_row_add_col`: Set to track main diagonals (where row + col is constant)
- `s_row_sub_col`: Set to track anti-diagonals (where row - col is constant)  
- `table`: List storing column positions of queens for each row
- `list_table`: Final result storing all valid solutions

**Core Algorithm (DFS + Backtracking):**

1. **Base Case**: When `r == n`, we've placed all `n` queens successfully, so format and save the current solution.

2. **Recursive Case**: For each row `r`, try placing a queen in each column `c`:
   - **Conflict Check**: Verify the position `(r,c)` doesn't conflict with existing queens using our tracking sets
   - **Place Queen**: Add constraints to all tracking sets and record column position
   - **Recurse**: Try to place queens in remaining rows
   - **Backtrack**: Remove all constraints and undo the queen placement

3. **Conflict Detection Logic**:
   ```python
   if all([r not in s_row, c not in s_col, r + c not in s_row_add_col, r - c not in s_row_sub_col]):
   ```
   This checks that no queen is already attacking position `(r,c)`

4. **Solution Formatting**: `format_table()` converts the compact representation (list of column indices) into the required string format with 'Q' and '.' characters.

**Time Complexity**: O`(N!)` - In the worst case, we explore all possible ways to place N queens
**Space Complexity**: `O(N)` - For the recursion stack and tracking sets

**Key Insight**: By using mathematical properties of diagonals (`row±col` relationships) and sets for `O(1)` lookups, this solution efficiently prunes invalid branches early in the search, making it much faster than a naive approach that checks the entire board for conflicts.

## Tags

recursion, backtracking