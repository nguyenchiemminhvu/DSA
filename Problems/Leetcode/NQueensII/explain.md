## Problem

https://leetcode.com/problems/n-queens-ii/description/

```
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return the number of distinct solutions to the n-queens puzzle.

Example 1:

Input: n = 4
Output: 2
Explanation: There are two distinct solutions to the 4-queens puzzle as shown.

Example 2:

Input: n = 1
Output: 1

Constraints:

1 <= n <= 9
```

## Observations

1. **Queen Attack Pattern**: A queen can attack any piece on the same row, column, or diagonal. This means no two queens can share:
   - The same row
   - The same column  
   - The same diagonal (both main diagonal and anti-diagonal)

2. **Diagonal Constraints**: 
   - Main diagonal (top-left to bottom-right): cells with the same `row - col` value
   - Anti-diagonal (top-right to bottom-left): cells with the same `row + col` value

3. **Search Space**: For an n×n board, we need to place exactly n queens, one in each row. This reduces the problem to finding valid column positions for each row.

4. **Backtracking Opportunity**: When we place a queen and later find no valid solution, we can backtrack by removing the queen and trying the next position.

5. **Counting vs Finding**: Unlike N-Queens I which asks for all solutions, this problem only needs the count, making it slightly more efficient as we don't need to store actual board configurations.

## Solution

The solution uses **backtracking with constraint tracking** to efficiently count all valid N-Queens configurations.

### Key Components:

1. **Constraint Sets**: Four sets track occupied positions:
   - `s_row`: occupied rows
   - `s_col`: occupied columns
   - `s_row_add_col`: occupied anti-diagonals (row + col)
   - `s_row_sub_col`: occupied main diagonals (row - col)

2. **DFS Recursion**: 
   - **Base case**: When `r == n`, we've successfully placed all queens → return 1
   - **Recursive case**: Try placing a queen in each column of the current row

3. **Constraint Checking**: Before placing a queen at position (r, c), verify:
   - Row `r` is not occupied
   - Column `c` is not occupied
   - Anti-diagonal `r + c` is not occupied
   - Main diagonal `r - c` is not occupied

4. **Backtracking**: After exploring all possibilities with a queen at (r, c):
   - Remove the queen from all constraint sets
   - Try the next column position

### Algorithm Flow:
```
1. Start with row 0
2. For each column in current row:
   a. Check if position is valid (no conflicts)
   b. If valid: place queen, update constraints, recurse to next row
   c. Count solutions from recursive call
   d. Backtrack: remove queen, restore constraints
3. Return total count of valid solutions
```

### Time Complexity: O(N!)
- In the worst case, we explore all possible ways to place N queens
- Each row has at most N choices, but constraints reduce this significantly

### Space Complexity: O(N)
- Four constraint sets, each storing at most N elements
- Recursion depth is N (one call per row)

## Tags

recursion, backtracking