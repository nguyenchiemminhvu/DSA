## Problem

https://leetcode.com/problems/cells-in-a-range-on-an-excel-sheet/description/

```
A cell (r, c) of an excel sheet is represented as a string "<col><row>" where:

<col> denotes the column number c of the cell. It is represented by alphabetical letters.
For example, the 1st column is denoted by 'A', the 2nd by 'B', the 3rd by 'C', and so on.
<row> is the row number r of the cell. The rth row is represented by the integer r.
You are given a string s in the format "<col1><row1>:<col2><row2>", where <col1> represents the column c1, <row1> represents the row r1, <col2> represents the column c2, and <row2> represents the row r2, such that r1 <= r2 and c1 <= c2.

Return the list of cells (x, y) such that r1 <= x <= r2 and c1 <= y <= c2. The cells should be represented as strings in the format mentioned above and be sorted in non-decreasing order first by columns and then by rows.

Example 1:

Input: s = "K1:L2"
Output: ["K1","K2","L1","L2"]
Explanation:
The above diagram shows the cells which should be present in the list.
The red arrows denote the order in which the cells should be presented.

Example 2:

Input: s = "A1:F1"
Output: ["A1","B1","C1","D1","E1","F1"]
Explanation:
The above diagram shows the cells which should be present in the list.
The red arrow denotes the order in which the cells should be presented.

Constraints:

s.length == 5
'A' <= s[0] <= s[3] <= 'Z'
'1' <= s[1] <= s[4] <= '9'
s consists of uppercase English letters, digits and ':'.
```

## Observations

1. **Input Format**: The string `s` represents a range in Excel format like "K1:L2" where:
   - First part (before ':') is the top-left cell (col1, row1)
   - Second part (after ':') is the bottom-right cell (col2, row2)

2. **Cell Representation**: Each cell is represented as `<column><row>` where:
   - Column: Single uppercase letter (A=1st column, B=2nd column, etc.)
   - Row: Single digit (1-9)

3. **Range Properties**:
   - r1 ≤ r2 (starting row ≤ ending row)
   - c1 ≤ c2 (starting column ≤ ending column)

4. **Output Requirements**:
   - Return all cells within the rectangular range
   - Sort first by columns, then by rows
   - Format: ["K1","K2","L1","L2"] for range "K1:L2"

5. **Key Insights**:
   - Need to convert letters to numbers for range iteration
   - `ord()` function helps convert characters to ASCII values
   - Column A = ASCII 65, so `ord(char) - ord('A')` gives 0-based index
   - Use nested loops: outer for columns, inner for rows

## Solution

**Approach**: Parse the range string and generate all cells within the rectangle.

**Algorithm**:
1. **Parse Input**: Split string by ':' to get start and end cells
2. **Extract Coordinates**: 
   - Convert column letters to 0-based indices using ASCII arithmetic
   - Extract row numbers directly as integers
3. **Generate Range**: Use nested comprehension to create all cell combinations
4. **Format Output**: Convert back to Excel format (letter + number)

**Example Walkthrough** (s = "K1:L2"):
- `ab = "K1"`, `cd = "L2"`
- `a = 10` (K), `b = 1`, `c = 11` (L), `d = 2`
- Column range: [10, 11] → [K, L]
- Row range: [1, 2] → [1, 2]
- Output: ["K1", "K2", "L1", "L2"]

**Time Complexity**: O((c-a+1) × (d-b+1)) - proportional to rectangle area
**Space Complexity**: O((c-a+1) × (d-b+1)) - for the output list

**Edge Cases**:
- Single cell: "A1:A1" → ["A1"]
- Single row: "A1:F1" → ["A1","B1","C1","D1","E1","F1"] 
- Single column: "A1:A5" → ["A1","A2","A3","A4","A5"]

# Tags

