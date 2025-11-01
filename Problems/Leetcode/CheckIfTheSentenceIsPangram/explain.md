## Problem

https://leetcode.com/problems/check-if-the-sentence-is-pangram/

```
A pangram is a sentence where every letter of the English alphabet appears at least once.

Given a string sentence containing only lowercase English letters, return true if sentence is a pangram, or false otherwise.

Example 1:

Input: sentence = "thequickbrownfoxjumpsoverthelazydog"
Output: true
Explanation: sentence contains at least one of every letter of the English alphabet.

Example 2:

Input: sentence = "leetcode"
Output: false

Constraints:

1 <= sentence.length <= 1000
sentence consists of lowercase English letters.
```

## Observations

1. **Pangram Definition**: A pangram requires all 26 letters of the English alphabet to appear at least once
2. **Input Constraints**: The sentence contains only lowercase English letters (a-z)
3. **Core Challenge**: We need to verify that every letter from 'a' to 'z' appears in the input string
4. **Approach Options**: 
   - Use a frequency counter/dictionary to track which letters we've seen
   - Use a set to collect unique characters and check if size equals 26
   - Use bit manipulation to mark seen characters

## Solution

The provided solution uses a **frequency counting approach with a clever validation technique**:

### Algorithm Breakdown:

1. **Initialize Counter**: Create a dictionary with all 26 lowercase letters, each set to count `1`
   ```python
   d = {}
   for c in string.ascii_lowercase:
       d[c] = 1  # Each letter needs to be "found" once
   ```

2. **Process Input**: For each character in the sentence, decrement its count in the dictionary
   ```python
   for c in sentence:
       d[c] -= 1  # Mark this letter as "found"
   ```

3. **Validate Pangram**: Check if all letters have been found (count <= 0)
   ```python
   return all((v <= 0) for k, v in d.items())
   ```

### Key Insights:

- **Smart Initialization**: Starting with count `1` means we need each letter to appear at least once to make the count ≤ 0
- **Efficient Validation**: Using `all()` with a generator expression is memory efficient
- **Handles Duplicates**: If a letter appears multiple times, the count goes negative, which still satisfies `<= 0`

### Time & Space Complexity:
- **Time**: O(n + 26) = O(n) where n is the length of the sentence
- **Space**: O(26) = O(1) constant space for the dictionary

### Alternative Approaches:

1. **Set-based approach** (more intuitive):
   ```python
   def checkIfPangram(self, sentence: str) -> bool:
       return len(set(sentence)) == 26
   ```

2. **Boolean array approach**:
   ```python
   def checkIfPangram(self, sentence: str) -> bool:
       seen = [False] * 26
       for c in sentence:
           seen[ord(c) - ord('a')] = True
       return all(seen)
   ```

The given solution is elegant and demonstrates a creative use of counting logic!

## Tags

- Hash Table / Dictionary
- String Processing
- Frequency Counting
- Pangram Detection

