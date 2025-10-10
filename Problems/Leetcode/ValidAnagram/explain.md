## Problem

https://leetcode.com/problems/valid-anagram/description/

```
Given two strings s and t, return true if t is an anagram of s, and false otherwise.

Example 1:

Input: s = "anagram", t = "nagaram"

Output: true

Example 2:

Input: s = "rat", t = "car"

Output: false

Constraints:

1 <= s.length, t.length <= 5 * 104
s and t consist of lowercase English letters.

Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?
```

## Observations

1. **Anagram Definition**: Two strings are anagrams if they contain exactly the same characters with the same frequency, just rearranged.

2. **Character Frequency**: The core insight is that if two strings are anagrams, the frequency of each character must be identical in both strings.

3. **Length Check**: If the strings have different lengths, they cannot be anagrams (though this solution doesn't explicitly check this upfront).

4. **ASCII Range**: The solution uses an array of size 128 to cover the full ASCII character set, which is more than needed since the problem states only lowercase English letters are used.

5. **Two-Pass Approach**: The algorithm uses two separate loops - one to increment frequencies for string `s` and another to decrement frequencies for string `t`.

6. **Final Verification**: After processing both strings, all frequency counts should be zero if the strings are anagrams.

## Solution

The provided solution uses a **frequency counting** approach:

1. **Initialize Frequency Array**: Create an array `fs` of size 128 (ASCII range) initialized to zeros.

2. **Count Characters in First String**: Iterate through string `s` and increment the frequency count for each character using `ord(c)` as the index.

3. **Subtract Characters from Second String**: Iterate through string `t` and decrement the frequency count for each character.

4. **Verify Balance**: Use `all(f == 0 for f in fs)` to check if all frequency counts are zero. If yes, the strings are anagrams.

### Time Complexity: O(n + m)
- Where n and m are the lengths of strings s and t respectively
- We traverse each string once

### Space Complexity: O(1)
- Fixed-size array of 128 elements regardless of input size
- Since we only use lowercase English letters, we could optimize to size 26

### Alternative Approaches:

1. **Sorting**: Sort both strings and compare - O(n log n) time
2. **Hash Map**: Use a dictionary instead of fixed array - more memory efficient for sparse character sets
3. **Optimized Array**: Use array of size 26 for lowercase letters only

### Edge Cases Handled:
- Empty strings (both empty = anagram)
- Single characters
- Different lengths (will result in non-zero frequencies)
- Repeated characters

## Tags

array, string