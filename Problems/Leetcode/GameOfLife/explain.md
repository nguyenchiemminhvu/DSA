## Problem

https://leetcode.com/problems/game-of-life/description

The Game of Life is a cellular automaton devised by British mathematician John Horton Conway in 1970.

### Problem Statement
Given an `m x n` grid where each cell is either **live** (1) or **dead** (0), update the board to reflect its next state based on the following rules applied **simultaneously** to all cells:

1. Any live cell with **fewer than two** live neighbors **dies** (under-population)
2. Any live cell with **two or three** live neighbors **survives**
3. Any live cell with **more than three** live neighbors **dies** (over-population)
4. Any dead cell with **exactly three** live neighbors **becomes alive** (reproduction)

**Key Constraint**: The board must be updated simultaneously - you cannot update some cells first and then use their updated values to update other cells.

### Examples

**Example 1:**
```
Input:  [[0,1,0],
         [0,0,1],
         [1,1,1],
         [0,0,0]]

Output: [[0,0,0],
         [1,0,1],
         [0,1,1],
         [0,1,0]]
```

**Example 2:**
```
Input:  [[1,1],
         [1,0]]

Output: [[1,1],
         [1,1]]
```

### Constraints
- `m == board.length` and `n == board[i].length`
- `1 <= m, n <= 25`
- `board[i][j]` is 0 or 1

### Follow-up
1. Can you solve it **in-place** without using extra space?
2. How would you handle an **infinite board**?

## Observations

### Key Insights

1. **Simultaneous Update Requirement**: This is the critical challenge. We cannot modify cells in-place during iteration because updating a cell's state will affect the neighbor counts of adjacent cells that we haven't processed yet.

2. **Eight Neighbors**: Each cell has 8 neighbors in all 8 directions:
   - Horizontal: left, right
   - Vertical: up, down
   - Diagonal: 4 diagonal neighbors
   - Use direction vectors: `[(-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1)]`

3. **State Transition Logic**:
   - **Live cell (1)**:
     - Survives if: 2 or 3 live neighbors
     - Dies otherwise
   - **Dead cell (0)**:
     - Becomes alive if: exactly 3 live neighbors
     - Stays dead otherwise

4. **Boundary Handling**: Only count neighbors that exist within the grid bounds using bounds checking: `0 <= ni < m and 0 <= nj < n`

5. **Space Trade-off**:
   - **Simple approach**: Create a copy of the grid, count neighbors from original, write to copy, then copy back (O(m*n) space)
   - **Optimal approach**: Use in-place encoding (e.g., state 2 = was 1 now 0, state 3 = was 0 now 1) to avoid extra space

### Pattern Recognition
- Oscillators (period-2): Blinker (3 cells in line), Toad
- Still lifes: Block (2x2), Beehive
- Spaceships: Glider (moves diagonally)

## Solution

### Approach 1: Create Temporary Copy (Simple & Clear)

**Time Complexity**: O(m × n × 8) = O(m × n) - visit each cell once, check 8 neighbors  
**Space Complexity**: O(m × n) - temporary grid

```python
class Solution:
    def gameOfLife(self, board: List[List[int]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        directions = [
            (-1, -1), (-1, 0), (-1, 1),
            (0, -1),           (0, 1),
            (1, -1),  (1, 0),  (1, 1)
        ]

        m, n = len(board), len(board[0])
        temp = [[0 for _ in range(n)] for _ in range(m)]
        
        for i in range(m):
            for j in range(n):
                live_neighbors = 0

                # Count live neighbors
                for dx, dy in directions:
                    ni, nj = i + dx, j + dy
                    if 0 <= ni < m and 0 <= nj < n and board[ni][nj] == 1:
                        live_neighbors += 1

                # Apply rules
                if board[i][j] == 1:  # Live cell
                    if live_neighbors == 2 or live_neighbors == 3:
                        temp[i][j] = 1
                    else:
                        temp[i][j] = 0
                else:  # Dead cell
                    if live_neighbors == 3:
                        temp[i][j] = 1
                    else:
                        temp[i][j] = 0

        # Copy back to original grid
        for i in range(m):
            for j in range(n):
                board[i][j] = temp[i][j]
```

**Algorithm Explanation**:
1. Create a temporary grid to store the new state
2. For each cell, count its live neighbors by checking all 8 directions
3. Apply the 4 rules based on the cell's current state and live neighbor count
4. Copy the temporary grid back to the original board

---

### Approach 2: In-Place Solution (Optimal Space)

**Time Complexity**: O(m × n)  
**Space Complexity**: O(1) - excluding output

**Idea**: Use state encoding to track both old and new values:
- `0`: was dead, becomes dead
- `1`: was alive, becomes alive
- `2`: was alive, becomes dead
- `3`: was dead, becomes alive

```python
class Solution:
    def gameOfLife(self, board: List[List[int]]) -> None:
        directions = [(-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1)]
        m, n = len(board), len(board[0])
        
        # First pass: Mark state changes
        for i in range(m):
            for j in range(n):
                live_neighbors = 0
                
                for dx, dy in directions:
                    ni, nj = i + dx, j + dy
                    if 0 <= ni < m and 0 <= nj < n and board[ni][nj] in [1, 2]:
                        # 1 = alive, 2 = was alive now dead
                        live_neighbors += 1
                
                if board[i][j] == 1:  # Currently alive
                    if live_neighbors < 2 or live_neighbors > 3:
                        board[i][j] = 2  # Dies
                else:  # Currently dead
                    if live_neighbors == 3:
                        board[i][j] = 3  # Becomes alive
        
        # Second pass: Decode state to final values
        for i in range(m):
            for j in range(n):
                if board[i][j] == 2:
                    board[i][j] = 0
                elif board[i][j] == 3:
                    board[i][j] = 1
```

**Key Points**:
- States 2 and 3 are only used as temporary markers
- When counting neighbors, check for `board[ni][nj] in [1, 2]` (both alive states)
- Final pass converts encoded states back to 0 and 1

---

### Comparison

| Approach | Time | Space | Pros | Cons |
|----------|------|-------|------|------|
| Temporary Copy | O(mn) | O(mn) | Simple, clear logic | Uses extra space |
| In-Place | O(mn) | O(1) | Space optimal, interview favorite | More complex, harder to debug |

**Recommendation**: Use temporary copy for clarity unless explicitly asked for in-place solution.

# Tags

**Concepts**: Array, Matrix, Simulation, Cellular Automaton  
**Difficulty**: Medium  
**Category**: Matrix Manipulation, Game Theory

