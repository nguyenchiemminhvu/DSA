## Problem

https://leetcode.com/problems/verifying-an-alien-dictionary/description/

```
In an alien language, surprisingly, they also use English lowercase letters, but possibly in a different order. The order of the alphabet is some permutation of lowercase letters.

Given a sequence of words written in the alien language, and the order of the alphabet, return true if and only if the given words are sorted lexicographically in this alien language.

Example 1:

Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
Output: true
Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.

Example 2:

Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
Output: false
Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1], hence the sequence is unsorted.

Example 3:

Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
Output: false
Explanation: The first three characters "app" match, and the second string is shorter (in size.) According to lexicographical rules "apple" > "app", because 'l' > '∅', where '∅' is defined as the blank character which is less than any other character (More info).

Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 20
order.length == 26
All characters in words[i] and order are English lowercase letters.
```

## Observations

1. **Custom Alphabet Order**: The alien language uses the same 26 lowercase English letters but in a different order than our standard alphabet.

2. **Lexicographical Sorting**: We need to verify if the given words are sorted according to the alien dictionary order, not the standard English order.

3. **Character-by-Character Comparison**: To determine if two words are in correct order, we need to compare them character by character using the alien alphabet ordering.

4. **Key Insight**: We can map each character in the alien order to its position (index), then convert words to arrays of integers representing their character positions. This allows us to use standard list comparison in Python.

5. **Edge Cases**:
   - Words with common prefixes (like "app" and "apple")
   - Words of different lengths
   - Identical words (should be considered sorted)

## Solution

1. **Create Character Mapping**: Build a dictionary that maps each character in the alien order to its position (0-25). This gives us the relative ordering of characters.

2. **Convert Words to Position Arrays**: For each pair of consecutive words, convert them to arrays where each character is replaced by its position in the alien alphabet.

3. **Lexicographical Comparison**: Use Python's built-in list comparison to check if the current word comes before the next word in lexicographical order.
   - `arr2 < arr1` means the second word should come before the first word, which violates the sorted order
   - Python's list comparison works lexicographically: it compares elements from left to right until it finds a difference

4. **Return Result**: If any pair violates the ordering, return False. If all pairs are in correct order, return True.

**Time Complexity**: O(N × M) where N is the number of words and M is the average length of words.
**Space Complexity**: O(1) for the mapping dictionary (always 26 characters) + O(M) for the temporary arrays.

**Why This Works:**
- By converting characters to their positions in the alien alphabet, we transform the problem into standard lexicographical comparison
- Python's list comparison `<` operator naturally handles the lexicographical ordering we need
- The approach handles all edge cases including different word lengths and common prefixes

# Tags

String, Hash Table, Array

