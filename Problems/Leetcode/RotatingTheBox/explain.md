## Problem

https://leetcode.com/problems/rotating-the-box/description/

You are given an `m x n` matrix `boxGrid` representing a side-view of a box. Each cell of the box is one of the following:

- A stone `'#'`
- A stationary obstacle `'*'`
- Empty `'.'`

The box is rotated 90 degrees clockwise, causing some of the stones to fall due to gravity. Each stone falls down until it lands on an obstacle, another stone, or the bottom of the box. Gravity does not affect the obstacles' positions, and the inertia from the box's rotation does not affect the stones' horizontal positions.

It is guaranteed that each stone in `boxGrid` rests on an obstacle, another stone, or the bottom of the box.

**Return** an `n x m` matrix representing the box after the rotation described above.

**Constraints:**
- `m == boxGrid.length`
- `n == boxGrid[i].length`
- `1 <= m, n <= 500`
- `boxGrid[i][j]` is either `'#'`, `'*'`, or `'.'`

## Observations

1. **Two-step process**: The problem can be decomposed into two independent operations:
   - **Step 1**: Rotate the matrix 90 degrees clockwise
   - **Step 2**: Apply gravity to each column of the rotated matrix

2. **Rotation mechanics**: A 90-degree clockwise rotation transforms:
   - Original column `j` → rotated row `j` (but reversed)
   - Original matrix of size `m x n` → rotated matrix of size `n x m`

3. **Gravity simulation**: Once rotated, stones fall in each column independently:
   - Obstacles `'*'` are fixed and immovable
   - Stones `'#'` fall until blocked by an obstacle or another stone
   - Empty cells `'.'` fill in after stones fall

4. **Processing strategy**: To simulate gravity efficiently:
   - Process each column separately
   - Iterate from bottom to top within each column
   - Track the next available position (`move_idx`) where a stone should fall to
   - When encountering an obstacle, reset the available position to just above it
   - When encountering a stone, move it to the available position and move the index up

5. **Edge cases**:
   - Obstacles completely block stones from falling further in that column
   - Multiple stones stack on top of each other
   - Stones already at the bottom don't move

## Solution

```python
class Solution:
    def rotateTheBox(self, mat: List[List[str]]) -> List[List[str]]:
        nr = len(mat)
        nc = len(mat[0])
        
        # Step 1: Rotate 90 degrees clockwise
        # Take each column as a row, then reverse
        rotated = [[mat[i][j] for i in range(nr - 1, -1, -1)] for j in range(nc)]
        
        # Update dimensions after rotation
        nr = len(rotated)  # n (original columns)
        nc = len(rotated[0])  # m (original rows)
        
        # Step 2: Apply gravity to each column
        for c in range(nc):
            move_idx = nr - 1  # Start from bottom
            
            # Process from bottom to top
            for i in range(nr - 1, -1, -1):
                if rotated[i][c] == '*':
                    # Obstacle blocks further movement
                    move_idx = i - 1
                elif rotated[i][c] == '#':
                    # Found a stone: clear current position and move to available spot
                    rotated[i][c] = '.'
                    rotated[move_idx][c] = '#'
                    move_idx -= 1
        
        return rotated
```

### Detailed Explanation

**Phase 1: Matrix Rotation (90° Clockwise)**

To rotate a matrix 90 degrees clockwise:
- Original `m x n` matrix becomes `n x m` matrix
- Column `j` (read bottom-to-top) becomes row `j` (read left-to-right)

```
Original (2 x 3):        After Rotation (3 x 2):
[#  .  #]               [#  #]
[#  #  *]               [.  #]
                        [#  *]
```

The list comprehension `[[mat[i][j] for i in range(nr - 1, -1, -1)] for j in range(nc)]` accomplishes this by:
- Outer loop: iterate through each column index `j`
- Inner loop: iterate through each row from bottom to top (using `range(nr - 1, -1, -1)`)

**Phase 2: Gravity Simulation**

For each column, simulate stones falling downward:

1. **Initialize**: `move_idx = nr - 1` (bottom position where stones can fall to)

2. **Iterate bottom-to-top**: Process each cell from bottom (`nr-1`) to top (`0`)

3. **Handle obstacles** (`'*'`):
   - Obstacles don't move; they block further falling
   - Update `move_idx = i - 1` (next available position is just above the obstacle)

4. **Handle stones** (`'#'`):
   - Clear the stone's current position: `rotated[i][c] = '.'`
   - Place stone at the next available position: `rotated[move_idx][c] = '#'`
   - Decrement `move_idx` for the next stone to fall

### Example Walkthrough

For `boxGrid = [["#",".","*","."],["#","#","*","."]]`:

**After Rotation:**
```
["#", "."]
["#", "#"]
["*", "*"]
[".", "."]
```

**Gravity Simulation - Column 0:**
- `i=3`: `'.'` → skip
- `i=2`: `'*'` → obstacle, set `move_idx = 1`
- `i=1`: `'#'` → stone, move to `rotated[1][0]`, `move_idx = 0`
- `i=0`: `'#'` → stone, move to `rotated[0][0]`, `move_idx = -1`

**Gravity Simulation - Column 1:**
- `i=3`: `'.'` → skip
- `i=2`: `'*'` → obstacle, set `move_idx = 1`
- `i=1`: `'#'` → stone, move to `rotated[1][1]`, `move_idx = 0`
- `i=0`: `'.'` → skip

**Final Result:**
```
["#", "."]
["#", "#"]
["*", "*"]
[".", "."]
```

### Complexity Analysis

- **Time Complexity**: $O(n \times m)$ where $n$ and $m$ are dimensions
  - Rotation: $O(n \times m)$ to build new matrix
  - Gravity: $O(n \times m)$ to process all cells once
- **Space Complexity**: $O(n \times m)$ for the rotated matrix (output)

# Tags

- Matrix Manipulation
- Rotation
- Gravity Simulation
- Array Processing
- Two-Pass Algorithm

