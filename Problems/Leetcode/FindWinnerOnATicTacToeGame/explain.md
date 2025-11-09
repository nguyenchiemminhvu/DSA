## Problem

https://leetcode.com/problems/find-winner-on-a-tic-tac-toe-game/description/

```
Tic-tac-toe is played by two players A and B on a 3 x 3 grid. The rules of Tic-Tac-Toe are:

Players take turns placing characters into empty squares ' '.
The first player A always places 'X' characters, while the second player B always places 'O' characters.
'X' and 'O' characters are always placed into empty squares, never on filled ones.
The game ends when there are three of the same (non-empty) character filling any row, column, or diagonal.
The game also ends if all squares are non-empty.
No more moves can be played if the game is over.
Given a 2D integer array moves where moves[i] = [rowi, coli] indicates that the ith move will be played on grid[rowi][coli]. return the winner of the game if it exists (A or B). In case the game ends in a draw return "Draw". If there are still movements to play return "Pending".

You can assume that moves is valid (i.e., it follows the rules of Tic-Tac-Toe), the grid is initially empty, and A will play first.

Example 1:

Input: moves = [[0,0],[2,0],[1,1],[2,1],[2,2]]
Output: "A"
Explanation: A wins, they always play first.

Example 2:

Input: moves = [[0,0],[1,1],[0,1],[0,2],[1,0],[2,0]]
Output: "B"
Explanation: B wins.

Example 3:

Input: moves = [[0,0],[1,1],[2,0],[1,0],[1,2],[2,1],[0,1],[0,2],[2,2]]
Output: "Draw"
Explanation: The game ends in a draw since there are no moves to make.

Constraints:

1 <= moves.length <= 9
moves[i].length == 2
0 <= rowi, coli <= 2
There are no repeated elements on moves.
moves follow the rules of tic tac toe.
```

## Observations

1. **Game Rules Understanding:**
   - Player A always goes first and uses 'X'
   - Player B goes second and uses 'O'
   - Players alternate turns
   - Game ends when someone gets 3 in a row (horizontally, vertically, or diagonally)
   - If all 9 squares are filled without a winner, it's a draw
   - If the game isn't complete and no winner exists, it's "Pending"

2. **Input Analysis:**
   - `moves` array represents the sequence of moves made
   - Each move is `[row, col]` indicating the position
   - Since players alternate, odd-indexed moves (0, 2, 4...) are by Player A, even-indexed moves (1, 3, 5...) are by Player B

3. **Win Condition Checking:**
   - Need to check after each move if the current player has won
   - Must check: 3 rows, 3 columns, 2 diagonals = 8 total winning conditions
   - Only need to check for the player who just made the move

4. **Return Values:**
   - "A" if Player A wins
   - "B" if Player B wins  
   - "Draw" if all 9 moves are made without a winner
   - "Pending" if game is incomplete and no winner yet

## Solution

**Approach: Simulation with Early Win Detection**

The solution simulates the tic-tac-toe game by:

1. **Board Initialization:** Create a 3x3 board filled with spaces
2. **Player Tracking:** Use a boolean flag `is_first` to track whose turn it is
3. **Move Processing:** For each move in the sequence:
   - Place the current player's symbol on the board
   - Check all possible win conditions for the current player
   - If a win is detected, immediately return the winner
   - Switch to the next player
4. **Final State:** If no winner is found after all moves, determine if it's a draw or pending

**Key Implementation Details:**

- **Player Mapping:** `player = { True: 'X', False: 'O' }` maps the boolean flag to symbols
- **Efficient Win Checking:** After each move, only check win conditions for the current player
- **Row Check:** `board[i] == [player[is_first]] * n` compares entire row at once
- **Column Check:** `[board[0][i], board[1][i], board[2][i]] == [player[is_first]] * n` constructs column and compares
- **Diagonal Checks:** Check both main diagonal `[0,0], [1,1], [2,2]` and anti-diagonal `[0,2], [1,1], [2,0]`

**Time Complexity:** O(n × m) where n = 3 (board size) and m = number of moves. Since the board is fixed at 3x3 and max 9 moves, this is effectively O(1).

**Space Complexity:** O(1) - uses a fixed 3x3 board regardless of input size.

**Edge Cases Handled:**
- Game ends early with a winner (most common case)
- All 9 squares filled without winner (draw)
- Game incomplete with no winner yet (pending)
- Minimum 1 move, maximum 9 moves as per constraints

# Tags

Array, Matrix, Simulation, Game Theory

