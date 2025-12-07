## Problem

https://leetcode.com/problems/number-of-valid-words-in-a-sentence/description/

```
A sentence consists of lowercase letters ('a' to 'z'), digits ('0' to '9'), hyphens ('-'), 
punctuation marks ('!', '.', and ','), and spaces (' ') only. Each sentence can be broken 
down into one or more tokens separated by one or more spaces ' '.

A token is a valid word if all three of the following are true:

1. It only contains lowercase letters, hyphens, and/or punctuation (no digits).
2. There is at most one hyphen '-'. If present, it must be surrounded by lowercase characters 
   ("a-b" is valid, but "-ab" and "ab-" are not valid).
3. There is at most one punctuation mark. If present, it must be at the end of the token 
   ("ab,", "cd!", and "." are valid, but "a!b" and "c.," are not valid).

Examples of valid words include "a-b.", "afad", "ba-c", "a!", and "!".

Given a string sentence, return the number of valid words in sentence.

Example 1:
Input: sentence = "cat and  dog"
Output: 3
Explanation: The valid words in the sentence are "cat", "and", and "dog".

Example 2:
Input: sentence = "!this  1-s b8d!"
Output: 0
Explanation: There are no valid words in the sentence.
"!this" is invalid because it starts with a punctuation mark.
"1-s" and "b8d" are invalid because they contain digits.

Example 3:
Input: sentence = "alice and  bob are playing stone-game10"
Output: 5
Explanation: The valid words in the sentence are "alice", "and", "bob", "are", and "playing".
"stone-game10" is invalid because it contains digits.

Constraints:
- 1 <= sentence.length <= 1000
- sentence only contains lowercase English letters, digits, ' ', '-', '!', '.', and ','.
- There will be at least 1 token.
```

## Observations

1. **Token Parsing**: The sentence needs to be split into tokens using space as delimiter. Multiple consecutive spaces should be handled correctly by `split()` which automatically handles this.

2. **Validation Rules**: Each token must satisfy three strict conditions:
   - **No digits**: Any digit makes the token invalid
   - **Hyphen rules**: At most one hyphen, must be in the middle (not at start/end), and must be surrounded by lowercase letters
   - **Punctuation rules**: At most one punctuation mark (`!`, `.`, `,`), and it must be at the end of the token

3. **Edge Cases to Consider**:
   - Single character tokens (like "a" or "!")
   - Tokens with only punctuation (like "!")
   - Tokens with hyphen at boundaries ("-ab", "ab-")
   - Multiple punctuation marks ("a!b", "c.,")
   - Punctuation not at the end ("a!b")
   - Multiple hyphens ("a-b-c")
   - Digits anywhere in the token

## Solution

### Approach: Character-by-Character Validation

The solution uses a helper function `valid(s)` to check if each token meets all the requirements.

**Algorithm:**
1. Split the sentence into tokens using `split()` - this handles multiple spaces automatically
2. For each token, validate it character by character:
   - Track hyphen count (max 1 allowed)
   - Track punctuation count (max 1 allowed)
   - Check each character:
     - If digit → immediately invalid
     - If punctuation → must be at end (index == len-1) and first punctuation
     - If hyphen → must be in middle, surrounded by letters, and first hyphen
     - If lowercase letter → continue
     - Otherwise → invalid
3. Count all valid tokens

**Key Implementation Details:**
- When encountering a hyphen, verify:
  - Not at position 0 or len(s)-1
  - Previous character is a letter: `s[i-1].isalpha()`
  - Next character is a letter: `s[i+1].isalpha()`
- When encountering punctuation:
  - Must be at last position: `i == len(s) - 1`
  - No previous punctuation: `punct == 0`

**Time Complexity:** $O(n \times m)$ where $n$ is the number of tokens and $m$ is the average length of each token

**Space Complexity:** $O(n)$ for storing the list of tokens from `split()`

# Tags
`string` `validation` `parsing`

