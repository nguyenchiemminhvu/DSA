## Problem

https://leetcode.com/problems/check-if-two-chessboard-squares-have-the-same-color/

```
You are given two strings, coordinate1 and coordinate2, representing the coordinates of a square on an 8 x 8 chessboard.

Below is the chessboard for reference.

Return true if these two squares have the same color and false otherwise.

The coordinate will always represent a valid chessboard square. The coordinate will always have the letter first (indicating its column), and the number second (indicating its row).

Example 1:

Input: coordinate1 = "a1", coordinate2 = "c3"

Output: true

Explanation:

Both squares are black.

Example 2:

Input: coordinate1 = "a1", coordinate2 = "h3"

Output: false

Explanation:

Square "a1" is black and "h3" is white.

Constraints:

coordinate1.length == coordinate2.length == 2
'a' <= coordinate1[0], coordinate2[0] <= 'h'
'1' <= coordinate1[1], coordinate2[1] <= '8'
```

## Observations

1. **Chessboard Pattern**: A chessboard has alternating colors in a checkerboard pattern. Adjacent squares have different colors.

2. **Coordinate System**: 
   - Columns are labeled 'a' through 'h' (0-7 when converted)
   - Rows are labeled '1' through '8' 

3. **Color Pattern Rule**: 
   - A square's color depends on whether the sum of its row and column indices is even or odd
   - If (row + column) is even → one color (e.g., black)
   - If (row + column) is odd → other color (e.g., white)

4. **Mathematical Insight**: 
   - Instead of checking (row + column) % 2, we can use (row - column) % 2
   - This works because: (row + column) % 2 == (row - column) % 2
   - Two squares have the same color if their (row - column) values have the same parity

## Solution

The solution uses a clever mathematical approach:

1. **Parse Coordinates**:
   - Extract row: `int(a[1])` (convert '1'-'8' to integers)
   - Extract column: `ord(a[0]) - ord('a')` (convert 'a'-'h' to 0-7)

2. **Calculate Color Indicator**:
   - Use `abs(r - c) & 1` to get the parity of |row - column|
   - `& 1` is equivalent to `% 2` but faster (bitwise AND with 1)
   - `abs()` ensures we get consistent results regardless of whether row > column

3. **Compare Colors**:
   - Two squares have the same color if their parity values are equal
   - Return `abs(r - c) & 1 == abs(rr - cc) & 1`

**Example Walkthrough**:
- "a1": row=1, col=0 → |1-0| & 1 = 1 & 1 = 1
- "c3": row=3, col=2 → |3-2| & 1 = 1 & 1 = 1
- Both return 1, so same color → return True

**Time Complexity**: O(1)
**Space Complexity**: O(1)

# Tags

- Math
- Bit Manipulation
- Pattern Recognition

