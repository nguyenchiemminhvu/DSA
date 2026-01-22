## Problem

https://leetcode.com/problems/vowel-consonant-score/description/

```
You are given a string s consisting of lowercase English letters, spaces, and digits.

Let v be the number of vowels in s and c be the number of consonants in s.

A vowel is one of the letters 'a', 'e', 'i', 'o', or 'u', while any other letter in the English alphabet is considered a consonant.

The score of the string s is defined as follows:
- If c > 0, the score = floor(v / c) where floor denotes rounding down to the nearest integer.
- Otherwise, the score = 0.

Return an integer denoting the score of the string.

Example 1:
Input: s = "cooear"
Output: 2
Explanation: v = 4 vowels ('o', 'o', 'e', 'a'), c = 2 consonants ('c', 'r')
Score = floor(4 / 2) = 2

Example 2:
Input: s = "axeyizou"
Output: 1
Explanation: v = 5 vowels ('a', 'e', 'i', 'o', 'u'), c = 3 consonants ('x', 'y', 'z')
Score = floor(5 / 3) = 1

Example 3:
Input: s = "au 123"
Output: 0
Explanation: c = 0 (no consonants), so score = 0

Constraints:
- 1 <= s.length <= 100
- s consists of lowercase English letters, spaces and digits.
```

## Observations

1. **Character Classification**: We need to count only:
   - Vowels: 'a', 'e', 'i', 'o', 'u'
   - Consonants: lowercase English letters that are NOT vowels
   - Ignore: spaces and digits

2. **Edge Case**: When there are no consonants (c = 0), we must return 0 to avoid division by zero

3. **Integer Division**: Python's `//` operator performs floor division, which is exactly what we need

4. **String Membership Check**: Using `in 'aeiou'` is efficient for checking vowels, and `in string.ascii_lowercase` ensures we only count lowercase letters

## Solution

```python
import string

class Solution:
    def vowelConsonantScore(self, s: str) -> int:
        vow = 0
        con = 0
        
        # Count vowels and consonants
        for c in s:
            if c in 'aeiou':
                vow += 1
            elif c in string.ascii_lowercase:
                con += 1
        
        # Return floor division or 0 if no consonants
        return vow // con if con > 0 else 0
```

**Algorithm**:
1. Initialize counters for vowels and consonants
2. Iterate through each character in the string:
   - If it's a vowel ('a', 'e', 'i', 'o', 'u'), increment vowel counter
   - Else if it's a lowercase letter (consonant), increment consonant counter
   - Ignore spaces and digits
3. Return `vow // con` if `con > 0`, otherwise return `0`

**Complexity Analysis**:
- **Time Complexity**: O(n) where n is the length of string s, as we iterate through the string once
- **Space Complexity**: O(1) as we only use two integer variables

# Tags
#string #counting #math #easy

