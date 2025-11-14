## Problem

https://leetcode.com/problems/hexadecimal-and-hexatrigesimal-conversion/description/

```
You are given an integer n.

Return the concatenation of the hexadecimal representation of n2 and the hexatrigesimal representation of n3.

A hexadecimal number is defined as a base-16 numeral system that uses the digits 0 – 9 and the uppercase letters A - F to represent values from 0 to 15.

A hexatrigesimal number is defined as a base-36 numeral system that uses the digits 0 – 9 and the uppercase letters A - Z to represent values from 0 to 35.

Example 1:

Input: n = 13

Output: "A91P1"

Explanation:

n2 = 13 * 13 = 169. In hexadecimal, it converts to (10 * 16) + 9 = 169, which corresponds to "A9".
n3 = 13 * 13 * 13 = 2197. In hexatrigesimal, it converts to (1 * 362) + (25 * 36) + 1 = 2197, which corresponds to "1P1".
Concatenating both results gives "A9" + "1P1" = "A91P1".

Example 2:

Input: n = 36

Output: "5101000"

Explanation:

n2 = 36 * 36 = 1296. In hexadecimal, it converts to (5 * 162) + (1 * 16) + 0 = 1296, which corresponds to "510".
n3 = 36 * 36 * 36 = 46656. In hexatrigesimal, it converts to (1 * 363) + (0 * 362) + (0 * 36) + 0 = 46656, which corresponds to "1000".
Concatenating both results gives "510" + "1000" = "5101000".

Constraints:

1 <= n <= 1000
```

## Observations

1. **Problem Requirements**: 
   - Calculate n² and convert to hexadecimal (base-16)
   - Calculate n³ and convert to hexatrigesimal (base-36)
   - Concatenate both representations

2. **Base Conversion Understanding**:
   - Hexadecimal uses digits 0-9 and letters A-F (16 symbols total)
   - Hexatrigesimal uses digits 0-9 and letters A-Z (36 symbols total)
   - Both use positional notation where each position represents a power of the base

3. **Algorithm Pattern**:
   - Need a general base conversion function that can handle any base
   - The conversion process: repeatedly divide by base and collect remainders
   - Build result by taking remainders and mapping them to appropriate symbols

4. **Key Insights**:
   - The `keys` string "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" provides all 36 possible symbols
   - For base-16, we only use first 16 characters (0-9, A-F)
   - For base-36, we use all 36 characters (0-9, A-Z)
   - String reversal is needed because we collect digits from least to most significant

## Solution

### Approach: Generic Base Conversion

The solution uses a helper function `to_base(val, base)` that converts any integer to any base representation:

1. **Base Conversion Algorithm**:
   ```
   while val > 0:
       digit = val % base     # Get the rightmost digit in target base
       result = digit + result # Prepend digit to result
       val = val // base      # Remove the rightmost digit
   ```

2. **Implementation Details**:
   - Use a character map `keys = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"`
   - Build string from right to left, then reverse at the end
   - `val % base` gives the remainder (digit value)
   - `keys[val % base]` maps digit value to its character representation

3. **Step-by-step for Example 1 (n=13)**:
   - n² = 169 → base-16: 169÷16=10 remainder 9, 10÷16=0 remainder 10(A) → "A9"
   - n³ = 2197 → base-36: 2197÷36=61 remainder 1, 61÷36=1 remainder 25(P), 1÷36=0 remainder 1 → "1P1"
   - Result: "A9" + "1P1" = "A91P1"

4. **Time Complexity**: O(log₁₆(n²) + log₃₆(n³)) = O(log n)
5. **Space Complexity**: O(log n) for the result strings

# Tags

string, bit manipulation