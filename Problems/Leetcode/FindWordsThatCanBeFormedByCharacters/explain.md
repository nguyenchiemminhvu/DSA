## Problem

https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/description/

```
You are given an array of strings words and a string chars.

A string is good if it can be formed by characters from chars (each character can only be used once for each word in words).

Return the sum of lengths of all good strings in words.

Example 1:

Input: words = ["cat","bt","hat","tree"], chars = "atach"
Output: 6
Explanation: The strings that can be formed are "cat" and "hat" so the answer is 3 + 3 = 6.

Example 2:

Input: words = ["hello","world","leetcode"], chars = "welldonehoneyr"
Output: 10
Explanation: The strings that can be formed are "hello" and "world" so the answer is 5 + 5 = 10.

Constraints:

1 <= words.length <= 1000
1 <= words[i].length, chars.length <= 100
words[i] and chars consist of lowercase English letters.
```

## Observations

1. **Character Frequency Constraint**: Each character in `chars` can only be used once per word. This means we need to count the frequency of each character in `chars` and ensure no word requires more of any character than what's available.

2. **Independent Word Validation**: Each word in `words` is evaluated independently - the characters used for one word don't affect the availability for other words.

3. **Frequency Comparison Approach**: For each word, we need to:
   - Count the frequency of each character in the word
   - Compare it with the frequency of characters in `chars`
   - If the word requires more of any character than available in `chars`, it's invalid

4. **Lowercase Letters Only**: The constraint guarantees only lowercase English letters (a-z), making it efficient to use a fixed-size array of 26 elements for character counting.

5. **Sum of Valid Lengths**: We only need to return the total length of all "good" words, not the words themselves.

## Solution

The solution uses a **frequency counting approach** with the following strategy:

### Algorithm Steps:

1. **Create Character Frequency Map for `chars`**:
   - Use an array `f_chars` of size 26 to count frequency of each character in `chars`
   - Use lambda function `f_get_idx = lambda x: ord(x) - ord('a')` to map characters to array indices

2. **For Each Word in `words`**:
   - Create a frequency array `f_word` for the current word
   - Count frequency of each character in the word
   
3. **Validate Word**:
   - Compare `f_word[i]` with `f_chars[i]` for each character index
   - If any `f_chars[i] < f_word[i]`, the word cannot be formed (not enough characters)
   - If all characters are available in sufficient quantity, add the word's length to result

### Complexity Analysis:

- **Time Complexity**: O(N + M)
  - Where N is the total number of characters in all words
  - M is the length of `chars`
  - Each character is processed once for frequency counting
  - The validation loop runs at most 26 times per word (constant)

- **Space Complexity**: O(1)
  - Fixed-size arrays of length 26 regardless of input size
  - Only using constant extra space

### Example Trace:

For `words = ["cat","bt","hat","tree"]`, `chars = "atach"`:

1. `f_chars = [2,0,1,0,0,...,1,1,0]` (a:2, c:1, h:1, t:1)
2. Check "cat": needs a:1, c:1, t:1 → Valid ✓ (length 3)
3. Check "bt": needs b:1, t:1 → Invalid ✗ (no 'b' in chars)
4. Check "hat": needs a:1, h:1, t:1 → Valid ✓ (length 3)
5. Check "tree": needs e:2, r:1, t:1 → Invalid ✗ (no 'e' or 'r' in chars)

Result: 3 + 3 = 6

# Tags
- Hash Table
- String
- Counting
- Array

