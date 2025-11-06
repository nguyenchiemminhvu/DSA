## Problem

https://leetcode.com/problems/snake-in-matrix/

```
There is a snake in an n x n matrix grid and can move in four possible directions. Each cell in the grid is identified by the position: grid[i][j] = (i * n) + j.

The snake starts at cell 0 and follows a sequence of commands.

You are given an integer n representing the size of the grid and an array of strings commands where each command[i] is either "UP", "RIGHT", "DOWN", and "LEFT". It's guaranteed that the snake will remain within the grid boundaries throughout its movement.

Return the position of the final cell where the snake ends up after executing commands.

Example 1:

Input: n = 2, commands = ["RIGHT","DOWN"]

Output: 3

Explanation:

0	1
2	3

0	1
2	3

0	1
2	3

Example 2:

Input: n = 3, commands = ["DOWN","RIGHT","UP"]

Output: 1

Explanation:

0	1	2
3	4	5
6	7	8

0	1	2
3	4	5
6	7	8

0	1	2
3	4	5
6	7	8

0	1	2
3	4	5
6	7	8

Constraints:

2 <= n <= 10
1 <= commands.length <= 100
commands consists only of "UP", "RIGHT", "DOWN", and "LEFT".
The input is generated such the snake will not move outside of the boundaries.
```

## Observations

1. **Grid Indexing**: The problem uses a specific formula to convert 2D coordinates (row, column) to a 1D index: `position = row * n + column`. This is a standard row-major order indexing.

2. **Movement Mapping**: Each direction command translates to a coordinate change:
   - UP: Move one row up (row - 1)
   - DOWN: Move one row down (row + 1)
   - LEFT: Move one column left (column - 1)
   - RIGHT: Move one column right (column + 1)

3. **Coordinate Tracking**: Instead of tracking the actual position number, it's more efficient to track the row and column coordinates separately and convert to the final position at the end.

4. **Boundary Safety**: The problem guarantees that the snake won't move outside boundaries, so no boundary checking is needed.

## Solution

1. **Setup Movement Dictionary**: Create a mapping from command strings to coordinate deltas (row_change, column_change).

2. **Initialize Position**: Start at (0, 0) which corresponds to position 0 in the grid.

3. **Process Commands**: For each command:
   - Look up the direction vector from the movement dictionary
   - Update the current row and column coordinates

4. **Convert to Position**: Use the formula `row * n + column` to convert the final 2D coordinates back to the 1D position index.

**Time Complexity**: O(m) where m is the number of commands
**Space Complexity**: O(1) - only using constant extra space for the movement dictionary and variables

**Key Insights:**
- The solution avoids repeatedly calculating position indices during movement
- By tracking coordinates separately, we only need one multiplication at the end
- The movement dictionary provides clean, readable code for direction handling

# Tags

array