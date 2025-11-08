## Problem

https://leetcode.com/problems/replace-all-digits-with-characters/

```
You are given a 0-indexed string s that has lowercase English letters in its even indices and digits in its odd indices.

You must perform an operation shift(c, x), where c is a character and x is a digit, that returns the xth character after c.

For example, shift('a', 5) = 'f' and shift('x', 0) = 'x'.
For every odd index i, you want to replace the digit s[i] with the result of the shift(s[i-1], s[i]) operation.

Return s after replacing all digits. It is guaranteed that shift(s[i-1], s[i]) will never exceed 'z'.

Note that shift(c, x) is not a preloaded function, but an operation to be implemented as part of the solution.

Example 1:

Input: s = "a1c1e1"
Output: "abcdef"
Explanation: The digits are replaced as follows:
- s[1] -> shift('a',1) = 'b'
- s[3] -> shift('c',1) = 'd'
- s[5] -> shift('e',1) = 'f'

Example 2:

Input: s = "a1b2c3d4e"
Output: "abbdcfdhe"
Explanation: The digits are replaced as follows:
- s[1] -> shift('a',1) = 'b'
- s[3] -> shift('b',2) = 'd'
- s[5] -> shift('c',3) = 'f'
- s[7] -> shift('d',4) = 'h'

Constraints:

1 <= s.length <= 100
s consists only of lowercase English letters and digits.
shift(s[i-1], s[i]) <= 'z' for all odd indices i.
```

## Observations

1. **Pattern Recognition**: The string alternates between lowercase letters (even indices) and digits (odd indices).
   - Even indices: a, c, e, ...
   - Odd indices: 1, 1, 1, ... (digits to be replaced)

2. **Shift Operation**: The core operation is `shift(c, x)` which moves from character `c` by `x` positions in the alphabet.
   - `shift('a', 1) = 'b'` (97 + 1 = 98)
   - `shift('c', 1) = 'd'` (99 + 1 = 100)
   - `shift('x', 0) = 'x'` (120 + 0 = 120)

3. **Algorithm Pattern**: 
   - Only process odd indices (1, 3, 5, ...)
   - For each odd index `i`, replace `s[i]` with `shift(s[i-1], int(s[i]))`
   - The character at `s[i-1]` (previous even index) is the base character
   - The digit at `s[i]` determines how many positions to shift forward

4. **ASCII Mathematics**: 
   - Convert character to ASCII: `ord(c)`
   - Get alphabet position: `ord(c) - ord('a')` gives 0-based position (a=0, b=1, ...)
   - Shift forward: `(position + shift_amount) % 26` handles wraparound
   - Convert back to character: `chr(ord('a') + new_position)`

5. **Edge Cases Handled**:
   - The problem guarantees no wraparound beyond 'z' is needed
   - String always has the alternating pattern (letters at even, digits at odd)
   - Minimum length is 1, maximum is 100

6. **Time Complexity**: O(n) where n is the length of string
7. **Space Complexity**: O(n) for converting string to list (strings are immutable in Python)

## Solution

1. **Convert to List**: `s = list(s)` - Strings are immutable in Python, so we convert to list for in-place modification.

2. **Iterate Odd Indices**: `for i in range(1, len(s), 2)` - Start at index 1, increment by 2 to hit only odd indices (1, 3, 5, ...).

3. **ASCII Shift Calculation**:
   - `ord(s[i - 1]) - ord('a')`: Convert the base character to alphabet position (0-25)
   - `+ int(s[i])`: Add the shift amount (digit value)
   - `% 26`: Handle alphabet wraparound (though problem guarantees no wraparound needed)
   - `ord('a') +`: Convert back to ASCII value
   - `chr(...)`: Convert ASCII value back to character

4. **Join Result**: `"".join(s)` - Convert the modified list back to string.

**Example Trace** (s = "a1c1e1"):
- i=1: s[0]='a', s[1]='1' → chr(ord('a') + ((ord('a')-ord('a') + 1) % 26)) = chr(97 + (0+1)) = 'b'
- i=3: s[2]='c', s[3]='1' → chr(ord('a') + ((ord('c')-ord('a') + 1) % 26)) = chr(97 + (2+1)) = 'd'  
- i=5: s[4]='e', s[5]='1' → chr(ord('a') + ((ord('e')-ord('a') + 1) % 26)) = chr(97 + (4+1)) = 'f'
- Result: "abcdef"

**Time Complexity**: O(n) - Single pass through half the string  
**Space Complexity**: O(n) - List conversion requires additional space

# Tags

string, ascii, character-manipulation, simulation

