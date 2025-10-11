## Problem

https://leetcode.com/problems/roman-to-integer/

```
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, 2 is written as II in Roman numeral, just two ones added together. 12 is written as XII, which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.
Given a roman numeral, convert it to an integer.

Example 1:

Input: s = "III"
Output: 3
Explanation: III = 3.

Example 2:

Input: s = "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.

Example 3:

Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

Constraints:

1 <= s.length <= 15
s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
It is guaranteed that s is a valid roman numeral in the range [1, 3999].
```

## Observations

1. **Basic Roman Numerals**: The problem involves converting Roman numerals to integers using the basic symbols:
   - I=1, V=5, X=10, L=50, C=100, D=500, M=1000

2. **Subtraction Cases**: There are 6 special cases where subtraction is used instead of addition:
   - IV (4), IX (9), XL (40), XC (90), CD (400), CM (900)
   - These occur when a smaller numeral appears before a larger one

3. **Pattern Recognition**: The key insight is that we need to check for these 2-character subtraction patterns first before processing single characters

4. **Greedy Approach**: Process the string from left to right, always trying to match the longest possible pattern (2 characters first, then 1 character)

5. **String Manipulation**: We consume the string by removing processed characters until it's empty

## Solution

1. **Initialize**: Create a dictionary mapping all Roman patterns to their integer values
2. **Process**: While the string is not empty:
   - First, check if the first 2 characters form a subtraction pattern
   - If yes, add that value and remove 2 characters
   - Otherwise, add the value of the first character and remove 1 character
3. **Return**: The accumulated sum

**Time Complexity**: O(n) where n is the length of the string
**Space Complexity**: O(1) as the dictionary size is constant

**Example Walkthrough** (`s = "MCMXCIV"`):
- `MC` → Check `MC` (not in subtraction list) → Process `M` (1000) → `s = "CMXCIV"`
- `CM` → Found subtraction pattern → Add 900 → `s = "XCIV"`
- `XC` → Found subtraction pattern → Add 90 → `s = "IV"`
- `IV` → Found subtraction pattern → Add 4 → `s = ""`
- **Result**: 1000 + 900 + 90 + 4 = 1994

## Tags

string, hash-table, greedy