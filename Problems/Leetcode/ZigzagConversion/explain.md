## Problem

https://leetcode.com/problems/zigzag-conversion/description/

```
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);

Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I

Example 3:

Input: s = "A", numRows = 1
Output: "A"

Constraints:

1 <= s.length <= 1000
s consists of English letters (lower-case and upper-case), ',' and '.'.
1 <= numRows <= 1000
```

## Observations

1. **Pattern Recognition**: The zigzag pattern creates a vertical "bounce" effect where characters move down from row 0 to row (numRows-1), then back up to row 0, and repeat.

2. **Direction Changes**: The direction reverses only at the boundaries:
   - At row 0 (top): start going down
   - At row (numRows-1) (bottom): start going up

3. **Edge Cases**: 
   - When `numRows == 1`: No zigzag needed, return original string
   - When `numRows >= len(s)`: All characters fit in separate rows vertically

4. **Row-by-Row Construction**: Instead of trying to calculate positions mathematically, we can simulate the zigzag movement and build each row incrementally.

5. **Memory Efficiency**: We only need to store `numRows` strings, making space complexity O(numRows).

## Solution

1. **Initialization**: 
   - Create `numRows` empty strings to represent each row
   - Start at row 0 with `going_down = False` (will become `True` immediately)

2. **Character Placement**:
   - For each character in the input string:
     - Add it to the current row
     - Check if we're at a boundary (top or bottom row)
     - If at boundary, reverse direction
     - Move to next row based on current direction

3. **Direction Logic**:
   - `going_down = True`: move down (increment row index)
   - `going_down = False`: move up (decrement row index)
   - Direction changes when `cur_row == 0` or `cur_row == numRows - 1`

4. **Result**: Concatenate all rows to form the final zigzag string

### Time & Space Complexity:
- **Time**: O(n) where n is the length of input string
- **Space**: O(n) for storing the result in rows

### Example Walkthrough:
For `s = "PAYPALISHIRING"`, `numRows = 3`:
```
Row 0: P   A   H   N     → "PAHN"
Row 1: A P L S I I G     → "APLSIIG" 
Row 2: Y   I   R         → "YIR"
Result: "PAHN" + "APLSIIG" + "YIR" = "PAHNAPLSIIGYIR"
```

## Tags

string