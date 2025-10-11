## Problem

https://leetcode.com/problems/excel-sheet-column-number/

```
Given a string columnTitle that represents the column title as appears in an Excel sheet, return its corresponding column number.

For example:

A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28 
...

Example 1:

Input: columnTitle = "A"
Output: 1

Example 2:

Input: columnTitle = "AB"
Output: 28

Example 3:

Input: columnTitle = "ZY"
Output: 701

Constraints:

1 <= columnTitle.length <= 7
columnTitle consists only of uppercase English letters.
columnTitle is in the range ["A", "FXSHRXW"].
```

## Observations

1. **Base-26 Number System**: This problem is essentially converting from a base-26 number system to decimal, but with a twist - there's no "zero" digit. The letters A-Z represent values 1-26 instead of 0-25.

2. **Position-based Values**: Each position in the string has a weight based on powers of 26:
   - Rightmost position (units): 26^0 = 1
   - Second from right: 26^1 = 26  
   - Third from right: 26^2 = 676
   - And so on...

3. **Character Mapping**: Each letter maps to a value:
   - A = 1, B = 2, C = 3, ..., Z = 26
   - This is calculated using `ord(c) - ord('A') + 1`

4. **Examples Analysis**:
   - "A" = 1 × 26^0 = 1
   - "AB" = A × 26^1 + B × 26^0 = 1 × 26 + 2 × 1 = 28
   - "ZY" = Z × 26^1 + Y × 26^0 = 26 × 26 + 25 × 1 = 676 + 25 = 701

## Solution

1. **Reverse the String**: `title[::-1]` reverses the input string so we can process it from the least significant digit (rightmost) to the most significant digit (leftmost).

2. **Iterate Through Characters**: For each character at position `i` (0-indexed from the right):
   - Calculate the character's numeric value: `ord(c) - ord('A') + 1`
   - Multiply by the position weight: `26 ** i`
   - Add to the running total

3. **Mathematical Formula**: For a string of length n, the formula is:
   ```
   result = Σ(i=0 to n-1) [char_value(i) × 26^i]
   ```
   where char_value(i) is the numeric value of the character at position i from the right.

**Time Complexity**: O(n) where n is the length of the column title
**Space Complexity**: O(1) if we don't count the reversed string, O(n) if we do

## Tags

string, math