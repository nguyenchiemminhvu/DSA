## Problem

https://leetcode.com/problems/determine-color-of-a-chessboard-square/

```
You are given coordinates, a string that represents the coordinates of a square of the chessboard. Below is a chessboard for your reference.

Return true if the square is white, and false if the square is black.

The coordinate will always represent a valid chessboard square. The coordinate will always have the letter first, and the number second.

Example 1:

Input: coordinates = "a1"
Output: false
Explanation: From the chessboard above, the square with coordinates "a1" is black, so return false.

Example 2:

Input: coordinates = "h3"
Output: true
Explanation: From the chessboard above, the square with coordinates "h3" is white, so return true.

Example 3:

Input: coordinates = "c7"
Output: false

Constraints:

coordinates.length == 2
'a' <= coordinates[0] <= 'h'
'1' <= coordinates[1] <= '8'
```

## Observations

1. **Chess board pattern**: A chess board has an alternating pattern of black and white squares.
2. **Coordinate system**: The chess board uses coordinates where:
   - Letters 'a' to 'h' represent columns (0-7 when converted to numbers)
   - Numbers '1' to '8' represent rows (1-8)
3. **Pattern recognition**: 
   - If we look at a chess board, the bottom-left square (a1) is black
   - The color alternates in a checkerboard pattern
   - Adjacent squares (horizontally or vertically) always have different colors
4. **Mathematical insight**: 
   - If we convert coordinates to numbers and check the sum of row and column:
     - Even sum → one color
     - Odd sum → other color
   - However, the solution uses `abs(r - c) % 2` instead of `(r + c) % 2`
   - Both approaches work, but they define opposite color mappings

## Solution

1. **Parse coordinates**: 
   - `r = int(coord[1])`: Extract the row number (1-8)
   - `c = ord(coord[0]) - ord('a')`: Convert column letter to number (0-7)

2. **Calculate color pattern**:
   - `abs(r - c) % 2`: Take absolute difference between row and column, then check if even
   - If the result is 0 (even), return `True` (white)
   - If the result is 1 (odd), return `False` (black)

**Why this works:**
- In a chess board, squares with the same parity (both even or both odd coordinates) have one color
- Squares with different parity have the opposite color
- The `abs(r - c) % 2` captures this pattern:
  - When `r` and `c` have same parity: `abs(r - c)` is even → `% 2 == 0` → white
  - When `r` and `c` have different parity: `abs(r - c)` is odd → `% 2 == 1` → black

**Examples verification:**
- `"a1"`: r=1, c=0 → `abs(1-0) % 2 = 1` → False (black) ✓
- `"h3"`: r=3, c=7 → `abs(3-7) % 2 = 0` → True (white) ✓
- `"c7"`: r=7, c=2 → `abs(7-2) % 2 = 1` → False (black) ✓

**Time Complexity:** O(1) - constant time operations
**Space Complexity:** O(1) - only using a few variables

# Tags

- Math
- Pattern Recognition
- Chess Board
- Coordinate System

