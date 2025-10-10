## Problem

https://leetcode.com/problems/word-pattern/description/

```
Given a pattern and a string s, find if s follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in s. Specifically:

Each letter in pattern maps to exactly one unique word in s.
Each unique word in s maps to exactly one letter in pattern.
No two letters map to the same word, and no two words map to the same letter.

Example 1:

Input: pattern = "abba", s = "dog cat cat dog"

Output: true

Explanation:

The bijection can be established as:

'a' maps to "dog".
'b' maps to "cat".

Example 2:

Input: pattern = "abba", s = "dog cat cat fish"

Output: false

Example 3:

Input: pattern = "aaaa", s = "dog cat cat dog"

Output: false

Constraints:

1 <= pattern.length <= 300
pattern contains only lower-case English letters.
1 <= s.length <= 3000
s contains only lowercase English letters and spaces ' '.
s does not contain any leading or trailing spaces.
All the words in s are separated by a single space.
```

## Observations

1. **Bijection Requirement**: The problem requires a one-to-one mapping (bijection) between characters in the pattern and words in the string. This means:
   - Each character must map to exactly one unique word
   - Each word must map to exactly one unique character
   - No character can map to multiple words
   - No word can map to multiple characters

2. **Length Check**: If the pattern length doesn't match the number of words, it's impossible to establish a bijection.

3. **Two-Way Mapping**: We need to track mappings in both directions:
   - Pattern character → Word (to ensure each character maps to the same word consistently)
   - Word → Pattern character (to ensure each word maps to the same character consistently)

4. **Edge Cases**:
   - Different lengths of pattern and words
   - Same character mapping to different words
   - Same word mapping to different characters

## Solution

1. **Split and Length Check**: Split the string into words and check if the count matches the pattern length.

2. **Two Hash Maps**: Use two dictionaries to maintain bidirectional mapping:
   - `dp`: Maps pattern characters to words
   - `ds`: Maps words to pattern characters

3. **Iterate and Validate**: For each character-word pair:
   - **Case 1**: Both mappings exist - verify they're consistent with current pair
   - **Case 2**: Neither mapping exists - create new mappings for both directions  
   - **Case 3**: Only one mapping exists - this violates bijection, return False

4. **Return True**: If all pairs are processed without violations, the pattern matches.

**Time Complexity**: O(n) where n is the length of pattern/number of words
**Space Complexity**: O(k) where k is the number of unique characters/words

**Key Insight**: The solution cleverly handles the bijection requirement by checking both directions of mapping simultaneously, ensuring that any violation of the one-to-one relationship is caught immediately.

## Tags

array, string, hash table