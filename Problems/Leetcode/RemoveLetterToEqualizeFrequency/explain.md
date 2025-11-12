## Problem

https://leetcode.com/problems/remove-letter-to-equalize-frequency/description/

```
You are given a 0-indexed string word, consisting of lowercase English letters. You need to select one index and remove the letter at that index from word so that the frequency of every letter present in word is equal.

Return true if it is possible to remove one letter so that the frequency of all letters in word are equal, and false otherwise.

Note:

The frequency of a letter x is the number of times it occurs in the string.
You must remove exactly one letter and cannot choose to do nothing.

Example 1:

Input: word = "abcc"
Output: true
Explanation: Select index 3 and delete it: word becomes "abc" and each character has a frequency of 1.

Example 2:

Input: word = "aazz"
Output: false
Explanation: We must delete a character, so either the frequency of "a" is 1 and the frequency of "z" is 2, or vice versa. It is impossible to make all present letters have equal frequency.

Constraints:

2 <= word.length <= 100
word consists of lowercase English letters only.
```

## Observations

1. **Problem Understanding**: We need to remove exactly one character from the string such that all remaining characters have equal frequency.

2. **Key Insight**: The brute force approach tries removing each character one by one and checks if the resulting string has all characters with equal frequency.

3. **Frequency Analysis**: After removing one character, we count the frequency of each remaining character and check if min frequency equals max frequency (meaning all frequencies are the same).

4. **Edge Cases to Consider**:
   - Strings with all characters having the same frequency already (need to remove one to maintain equality)
   - Strings where only one character appears more than others by exactly 1
   - Strings with only one unique character (removing one maintains equal frequency of 1)

5. **Time Complexity**: O(n²) where n is the length of the string
   - We try removing each of the n characters
   - For each removal, we count frequencies which takes O(n) time

6. **Space Complexity**: O(k) where k is the number of unique characters (at most 26 for lowercase letters)

## Solution

1. **Iterate through each position**: Try removing the character at each index from 0 to len(word)-1

2. **Create substring**: Form a new string `sub` by concatenating the part before index i and the part after index i

3. **Count frequencies**: Use Counter to count the frequency of each character in the remaining string

4. **Check equality**: If min frequency equals max frequency, it means all characters have the same frequency

5. **Return result**: Return True if any removal results in equal frequencies, False otherwise

**Example Walkthrough**:
- For "abcc":
  - Remove 'a' → "bcc": frequencies {b:1, c:2} → min≠max
  - Remove 'b' → "acc": frequencies {a:1, c:2} → min≠max  
  - Remove 'c' → "abc": frequencies {a:1, b:1, c:1} → min=max=1 ✓
  - Return True

- For "aazz":
  - Remove 'a' → "azz": frequencies {a:1, z:2} → min≠max
  - Remove 'a' → "azz": frequencies {a:1, z:2} → min≠max
  - Remove 'z' → "aaz": frequencies {a:2, z:1} → min≠max
  - Remove 'z' → "aaz": frequencies {a:2, z:1} → min≠max
  - Return False

# Tags

- String Manipulation
- Hash Table / Counter
- Brute Force
- Frequency Analysis

