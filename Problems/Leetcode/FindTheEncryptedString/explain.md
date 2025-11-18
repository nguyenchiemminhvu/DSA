## Problem

https://leetcode.com/problems/find-the-encrypted-string/

```
You are given a string s and an integer k. Encrypt the string using the following algorithm:

For each character c in s, replace c with the kth character after c in the string (in a cyclic manner).
Return the encrypted string.

Example 1:

Input: s = "dart", k = 3

Output: "tdar"

Explanation:

For i = 0, the 3rd character after 'd' is 't'.
For i = 1, the 3rd character after 'a' is 'd'.
For i = 2, the 3rd character after 'r' is 'a'.
For i = 3, the 3rd character after 't' is 'r'.

Example 2:

Input: s = "aaa", k = 1

Output: "aaa"

Explanation:

As all the characters are the same, the encrypted string will also be the same.

Constraints:

1 <= s.length <= 100
1 <= k <= 104
s consists only of lowercase English letters.
```

## Observations

1. **Cyclic Shift Pattern**: The problem asks us to replace each character with the character that is `k` positions ahead in a cyclic manner.

2. **Modular Arithmetic**: Since the shift is cyclic, we need to use modulo operation to handle cases where `k` is larger than the string length.

3. **Index Mapping**: For each position `i` in the original string, the encrypted character comes from position `(i + k) % len(s)`.

4. **Edge Cases**:
   - When `k` equals the string length, the string remains unchanged
   - When `k` is a multiple of string length, the result is the original string
   - When all characters are the same, the result is always the same string

5. **Time Complexity**: O(n) where n is the length of the string
6. **Space Complexity**: O(n) for the result string

## Solution

```python
class Solution:
    def getEncryptedString(self, s: str, k: int) -> str:
        return "".join(s[(i + k) % len(s)] for i in range(len(s)))
```

### Explanation

The solution uses a simple one-liner with list comprehension:

1. **Iterate through indices**: `for i in range(len(s))` - We iterate through each position in the original string.

2. **Calculate encrypted position**: `(i + k) % len(s)` - For each position `i`, we find the character that should replace it by:
   - Adding `k` to the current position `i`
   - Using modulo `len(s)` to wrap around when we exceed the string length

3. **Build result**: `"".join(...)` - We join all the encrypted characters to form the final string.

### Example Walkthrough

For `s = "dart"`, `k = 3`:
- Position 0 ('d'): `(0 + 3) % 4 = 3` → 't'
- Position 1 ('a'): `(1 + 3) % 4 = 0` → 'd' 
- Position 2 ('r'): `(2 + 3) % 4 = 1` → 'a'
- Position 3 ('t'): `(3 + 3) % 4 = 2` → 'r'

Result: "tdar"

### Key Insights

- **Modular arithmetic** elegantly handles the cyclic nature of the encryption
- **No need for separate handling** of edge cases since modulo naturally wraps around
- **Single pass solution** makes it both time and space efficient

# Tags

- String Manipulation
- Modular Arithmetic  
- Array/String Indexing
- Cyclic Operations

