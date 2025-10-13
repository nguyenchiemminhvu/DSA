## Problem

https://leetcode.com/problems/convert-a-number-to-hexadecimal/

```
Given a 32-bit integer num, return a string representing its hexadecimal representation. For negative integers, two’s complement method is used.

All the letters in the answer string should be lowercase characters, and there should not be any leading zeros in the answer except for the zero itself.

Note: You are not allowed to use any built-in library method to directly solve this problem.

Example 1:

Input: num = 26
Output: "1a"

Example 2:

Input: num = -1
Output: "ffffffff"

Constraints:

-231 <= num <= 231 - 1
```

## Observations

1. **Hexadecimal Base**: Hexadecimal is base-16, using digits 0-9 and letters a-f (representing 10-15).

2. **Bit Groups**: Each hex digit represents exactly 4 bits (since 2^4 = 16). A 32-bit integer can be represented by at most 8 hex digits.

3. **Negative Numbers**: For negative integers, we must use two's complement representation:
   - In two's complement, negative numbers are represented by flipping all bits and adding 1
   - For a 32-bit system, -1 becomes `0xFFFFFFFF` (all bits set to 1)
   - The formula: `0xFFFFFFFF + num + 1` converts a negative number to its unsigned 32-bit equivalent

4. **Extraction Strategy**: We can extract hex digits from right to left by:
   - Masking the last 4 bits using `num & 0xF` (0xF = 1111 in binary)
   - Right-shifting by 4 bits to process the next digit
   - Repeating until the number becomes 0

5. **Special Case**: Zero should return "0" directly to avoid an empty result.

## Solution

### Approach: Bit Manipulation

**Algorithm:**

1. **Setup hex character mapping**: Create a lookup array for hex digits (0-9, a-f).

2. **Handle negative numbers**: 
   - If `num < 0`, convert it to its 32-bit unsigned representation using two's complement
   - Formula: `0xFFFFFFFF + num + 1`
   - Example: `-1` becomes `0xFFFFFFFF + (-1) + 1 = 0xFFFFFFFF`

3. **Handle zero case**: If `num == 0`, return "0" immediately.

4. **Extract hex digits**:
   - Use a loop while `num > 0`
   - Extract the last 4 bits: `val = num & 0xF` (bitwise AND with 15)
   - Append the corresponding hex character: `hex_str[val]`
   - Right-shift by 4 bits: `num >>= 4` (divide by 16 in binary)

5. **Build result**: Since we extracted digits from right to left, reverse the result before returning.

**Example Walkthrough (num = 26):**
```
26 in binary: 00000000 00000000 00000000 00011010

Iteration 1:
  val = 26 & 0xF = 0b11010 & 0b1111 = 0b1010 = 10 → 'a'
  num = 26 >> 4 = 1

Iteration 2:
  val = 1 & 0xF = 0b0001 & 0b1111 = 0b0001 = 1 → '1'
  num = 1 >> 4 = 0

Result: ['a', '1'] → reversed → "1a"
```

**Example Walkthrough (num = -1):**
```
-1 converted: 0xFFFFFFFF + (-1) + 1 = 0xFFFFFFFF
Binary: 11111111 11111111 11111111 11111111

Extract 8 times (4 bits each):
  0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF → all 'f'

Result: "ffffffff"
```

**Complexity Analysis:**
- **Time Complexity**: O(1) - Maximum 8 iterations for 32-bit integer (32 bits / 4 bits per hex digit)
- **Space Complexity**: O(1) - Maximum 8 characters in the result string

**Key Insights:**
- The mask `0xF` (binary: 1111) isolates the rightmost 4 bits
- Right-shift `>>= 4` effectively divides by 16 and moves to the next hex digit
- Two's complement conversion `0xFFFFFFFF + num + 1` handles negative numbers correctly
- No built-in conversion functions are used, satisfying the problem constraints

## Tags

bit manipulation