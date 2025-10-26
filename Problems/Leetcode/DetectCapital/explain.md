## Problem

https://leetcode.com/problems/detect-capital/

```
We define the usage of capitals in a word to be right when one of the following cases holds:

All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital, like "Google".
Given a string word, return true if the usage of capitals in it is right.

Example 1:

Input: word = "USA"
Output: true

Example 2:

Input: word = "FlaG"
Output: false

Constraints:

1 <= word.length <= 100
word consists of lowercase and uppercase English letters.
```

## Observations

1. **Valid Capital Usage Patterns**: A word has correct capital usage if it follows exactly one of these three patterns:
   - **All uppercase**: "USA", "HELLO", "WORLD"  
   - **All lowercase**: "leetcode", "hello", "world"
   - **Only first letter capitalized**: "Google", "Apple", "Python"

2. **Invalid Patterns**: Any other combination is invalid:
   - "FlaG" - mixed case with uppercase not at beginning
   - "fLaG" - starts with lowercase but has uppercase letters
   - "FlAg" - first letter capitalized but has mixed case after

3. **Edge Cases**:
   - Single character words are always valid (either uppercase or lowercase)
   - Empty strings don't exist per constraints (length >= 1)

4. **Key Insight**: We can check the patterns in order of complexity:
   - First check if all characters are the same case (easiest)
   - Then check specific rules for mixed case scenarios

## Solution

The solution uses a **pattern-matching approach** that checks each valid case systematically:

### Algorithm Steps:

1. **Check Uniform Cases**: 
   ```python
   if all(c.islower() for c in word) or all(c.isupper() for c in word):
       return True
   ```
   - If all characters are lowercase OR all are uppercase → valid
   - This handles patterns like "hello" and "WORLD"

2. **Handle Mixed Cases**:
   ```python
   if word[0].islower():
       return False
   ```
   - If first character is lowercase but we reached here (not all lowercase) → invalid
   - This catches cases like "fLaG"

3. **First Letter Capitalized Case**:
   ```python
   if word[0].isupper():
       return not any(c.isupper() for c in word[1:])
   ```
   - If first letter is uppercase, check that NO other letters are uppercase
   - This handles the "Google" pattern vs "FlaG" pattern

4. **Fallback**: Return `True` (though this line is never reached given the logic)

### Time Complexity: O(n)
- We may scan the string up to 3 times in worst case
- Each scan is O(n) where n is the length of the word
- Overall: O(n)

### Space Complexity: O(1)
- Only using constant extra space for comparisons
- No additional data structures needed

### Example Traces:

**Example 1: "USA"**
- `all(c.islower())` → False
- `all(c.isupper())` → True
- Return `True` ✓

**Example 2: "leetcode"** 
- `all(c.islower())` → True
- Return `True` ✓

**Example 3: "Google"**
- `all(c.islower())` → False  
- `all(c.isupper())` → False
- `word[0].islower()` → False (G is uppercase)
- `word[0].isupper()` → True
- `any(c.isupper() for c in word[1:])` → False (oogle are all lowercase)
- Return `not False` = `True` ✓

**Example 4: "FlaG"**
- `all(c.islower())` → False
- `all(c.isupper())` → False  
- `word[0].islower()` → False (F is uppercase)
- `word[0].isupper()` → True
- `any(c.isupper() for c in word[1:])` → True (G is uppercase)
- Return `not True` = `False` ✓

## Tags

string