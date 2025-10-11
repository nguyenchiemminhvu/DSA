## Problem

https://leetcode.com/problems/reverse-prefix-of-word/

```
Given a 0-indexed string word and a character ch, reverse the segment of word that starts at index 0 and ends at the index of the first occurrence of ch (inclusive). If the character ch does not exist in word, do nothing.

For example, if word = "abcdefd" and ch = "d", then you should reverse the segment that starts at 0 and ends at 3 (inclusive). The resulting string will be "dcbaefd".
Return the resulting string.

Example 1:

Input: word = "abcdefd", ch = "d"
Output: "dcbaefd"
Explanation: The first occurrence of "d" is at index 3. 
Reverse the part of word from 0 to 3 (inclusive), the resulting string is "dcbaefd".
Example 2:

Input: word = "xyxzxe", ch = "z"
Output: "zxyxxe"
Explanation: The first and only occurrence of "z" is at index 3.
Reverse the part of word from 0 to 3 (inclusive), the resulting string is "zxyxxe".

Example 3:

Input: word = "abcd", ch = "z"
Output: "abcd"
Explanation: "z" does not exist in word.
You should not do any reverse operation, the resulting string is "abcd".

Constraints:

1 <= word.length <= 250
word consists of lowercase English letters.
ch is a lowercase English letter.
```

## Observations

1. **Key Requirements**:
   - Find the **first occurrence** of character `ch` in the string
   - Reverse only the prefix from index 0 to the first occurrence (inclusive)
   - If `ch` doesn't exist, return the original string unchanged

2. **Edge Cases**:
   - Character `ch` not found in the string → return original string
   - Character `ch` is at index 0 → reverse only the first character (no change)
   - Character `ch` is the last character → reverse the entire string

3. **String Manipulation**:
   - Need to split the string into two parts: prefix (to reverse) and suffix (unchanged)
   - Use Python's slicing and `[::-1]` for efficient string reversal

## Solution

1. **Find the character**: `word.index(ch)` finds the first occurrence of `ch`
   - If found, returns the index
   - If not found, raises `ValueError` which is caught by the except block

2. **Handle not found case**: Return the original string unchanged

3. **Split and reverse**:
   - `left = word[:found+1][::-1]` - Takes substring from 0 to `found+1` (inclusive) and reverses it
   - `right = word[found+1:]` - Takes the remaining substring after the found character

4. **Combine**: Concatenate the reversed prefix with the unchanged suffix

**Time Complexity**: O(n) where n is the length of the word
- `index()` operation: O(n) in worst case
- Slicing operations: O(n) in worst case
- String concatenation: O(n)

**Space Complexity**: O(n) for creating new strings

**Example walkthrough**:
- Input: `word = "abcdefd"`, `ch = "d"`
- `found = 3` (first 'd' at index 3)
- `left = "abcd"[::-1] = "dcba"`
- `right = "efd"`
- Result: `"dcba" + "efd" = "dcbaefd"`

## Tags

array, string