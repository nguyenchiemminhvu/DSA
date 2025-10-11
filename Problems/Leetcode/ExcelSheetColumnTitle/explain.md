## Problem

https://leetcode.com/problems/excel-sheet-column-title/

```
Given an integer columnNumber, return its corresponding column title as it appears in an Excel sheet.

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

Input: columnNumber = 1
Output: "A"

Example 2:

Input: columnNumber = 28
Output: "AB"

Example 3:

Input: columnNumber = 701
Output: "ZY"

Constraints:

1 <= columnNumber <= 231 - 1
```

## Observations

1. **This is a bijective base-26 system**: Excel column titles use A-Z (26 letters), but unlike standard base-26, there's no "zero" digit. The sequence goes A, B, ..., Z, AA, AB, ... instead of having a zero position.

2. **Key difference from standard base conversion**: In normal base systems, digits range from 0 to (base-1). Here, our "digits" range from 1 to 26 (A=1, B=2, ..., Z=26).

3. **Pattern analysis**:
   - 1-26: A, B, C, ..., Z (single letters)
   - 27-52: AA, AB, AC, ..., AZ (A + single letters)
   - 53-78: BA, BB, BC, ..., BZ (B + single letters)
   - 701: ZY (Z=26, Y=25, calculated as 26×26 + 25 = 676 + 25 = 701)

4. **The "subtract 1" trick**: Since there's no zero in this system, we need to adjust each step by subtracting 1 before the modulo operation to map the 1-based system to a 0-based calculation.

## Solution

### Base-26 Conversion with Bijective Mapping

The solution converts a decimal number to a bijective base-26 representation where:
- There are `26` "digits": `A, B, C, ..., Z`
- No zero digit exists (bijective property)
- Each position represents powers of `26`

### Step-by-step explanation:

1. **Subtract 1**: `n -= 1` converts from 1-based to 0-based indexing
   - Example: `n=28 → n=27`
   
2. **Get remainder**: `n % 26` gives us the current "digit" value (0-25)
   - Example: `27 % 26 = 1` (corresponds to 'B')
   
3. **Integer division**: `n //= 26` moves to the next position
   - Example: `27 // 26 = 1`
   
4. **Repeat**: Continue until `n` becomes `0`
   - Example: `n=1 → n=0 → 0 % 26 = 0` (corresponds to '`A`')
   
5. **Reverse and convert**: Reverse the collected digits and convert to characters
   - `[1, 0] → [0, 1] → ['A', 'B'] → "AB"`

### Example trace (n=28):
```
n=28: 28-1=27, 27%26=1→'B', 27//26=1, table=[1]
n=1:  1-1=0,   0%26=0→'A',  0//26=0,  table=[1,0]
Reverse: [0,1] → "AB"
```

### Why this works:
- The bijective base-26 system maps: A=1, B=2, ..., Z=26, AA=27, AB=28, ...
- By subtracting 1 each iteration, we handle the fact that there's no "zero" character
- The modulo operation extracts each base-26 digit from right to left
- Reversing gives us the correct left-to-right order

## Tags

string