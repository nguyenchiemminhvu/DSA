## Problem

https://leetcode.com/problems/base-7/

```
Given an integer num, return a string of its base 7 representation.

Example 1:

Input: num = 100
Output: "202"

Example 2:

Input: num = -7
Output: "-10"

Constraints:

-107 <= num <= 107
```

## Observations

1. **Base Conversion Problem**: We need to convert a decimal number to base 7 representation.
2. **Handle Special Cases**: 
   - Zero should return "0" directly
   - Negative numbers need special handling (preserve the sign)
3. **Base Conversion Algorithm**: Use the standard algorithm of repeatedly dividing by the base and collecting remainders
4. **String Building**: The digits are generated in reverse order, so we need to reverse the final string
5. **Valid Base 7 Digits**: Only digits 0-6 are valid in base 7 (note: the solution incorrectly includes '7' in the array)

## Solution

**Algorithm**: Standard base conversion using division and modulo operations

**Key Steps**:
1. Handle the zero case immediately
2. Store the sign and work with absolute value to simplify logic
3. Repeatedly divide by 7 and collect remainders (which become the digits)
4. Build string from right to left (digits are generated in reverse order)
5. Apply sign and reverse the string to get correct order

**Time Complexity**: O(log₇(n)) where n is the input number
**Space Complexity**: O(log₇(n)) for the result string

**Note**: There's a minor bug in the solution - `base7_vals` includes '7' which is not a valid base 7 digit, but since we only access indices 0-6 (from `num % 7`), this doesn't affect correctness.

# Tags

- Math
- Base Conversion
- String Manipulation
- Number Theory

