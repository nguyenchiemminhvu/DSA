## Problem

https://leetcode.com/problems/available-captures-for-rook/description/

```
You are given an 8 x 8 matrix representing a chessboard. There is exactly one white rook represented by 'R', some number of white bishops 'B', and some number of black pawns 'p'. Empty squares are represented by '.'.

A rook can move any number of squares horizontally or vertically (up, down, left, right) until it reaches another piece or the edge of the board. A rook is attacking a pawn if it can move to the pawn's square in one move.

Note: A rook cannot move through other pieces, such as bishops or pawns. This means a rook cannot attack a pawn if there is another piece blocking the path.

Return the number of pawns the white rook is attacking.

Example 1:

Input: board = [[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","R",".",".",".","p"],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]

Output: 3

Explanation:

In this example, the rook is attacking all the pawns.

Example 2:

Input: board = [[".",".",".",".",".",".","."],[".","p","p","p","p","p",".","."],[".","p","p","B","p","p",".","."],[".","p","B","R","B","p",".","."],[".","p","p","B","p","p",".","."],[".","p","p","p","p","p",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]

Output: 0

Explanation:

The bishops are blocking the rook from attacking any of the pawns.

Example 3:

Input: board = [[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","p",".",".",".","."],["p","p",".","R",".","p","B","."],[".",".",".",".",".",".",".","."],[".",".",".","B",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."]]

Output: 3

Explanation:

The rook is attacking the pawns at positions b5, d6, and f5.

Constraints:

board.length == 8
board[i].length == 8
board[i][j] is either 'R', '.', 'B', or 'p'
There is exactly one cell with board[i][j] == 'R'
```

## Observations

1. **Board constraints**: Fixed 8x8 chessboard with exactly one rook ('R')
2. **Movement rules**: Rook moves horizontally/vertically until hitting a piece or board boundary
3. **Piece interactions**: 
   - Pawns ('p') can be captured and should be counted
   - Bishops ('B') block the rook's path but cannot be captured
   - Empty squares ('.') allow continued movement
4. **Direction search**: Need to check all 4 directions (up, down, left, right) from rook's position
5. **Stopping conditions**: Stop when encountering any piece or reaching board edge

## Solution

**Approach**: Directional scanning from rook position

**Algorithm**:
1. **Locate the rook**: Scan the 8x8 board to find the rook's coordinates (r, c)
2. **Check each direction**: For up, down, left, and right directions:
   - Move step by step in that direction
   - If we encounter a bishop ('B'): stop searching this direction (blocked)
   - If we encounter a pawn ('p'): increment counter and stop searching this direction (captured)
   - If we reach board boundary: stop searching this direction
3. **Return total**: Sum of pawns found in all 4 directions

**Key implementation details**:
- Use range loops with appropriate step directions: `range(r-1, -1, -1)` for up, `range(r+1, n)` for down
- Break immediately after finding a piece (bishop or pawn) to avoid counting beyond obstacles
- Only increment count when finding a pawn, not when hitting a bishop

**Time Complexity**: O(1) - board size is constant 8x8, maximum 32 cells checked  
**Space Complexity**: O(1) - only using variables for position and count

# Tags

array, string