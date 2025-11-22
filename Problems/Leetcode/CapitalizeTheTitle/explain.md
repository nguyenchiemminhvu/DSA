## Problem

https://leetcode.com/problems/capitalize-the-title/description/

```
You are given a string title consisting of one or more words separated by a single space, where each word consists of English letters. Capitalize the string by changing the capitalization of each word such that:

If the length of the word is 1 or 2 letters, change all letters to lowercase.
Otherwise, change the first letter to uppercase and the remaining letters to lowercase.
Return the capitalized title.

Example 1:

Input: title = "capiTalIze tHe titLe"
Output: "Capitalize The Title"
Explanation:
Since all the words have a length of at least 3, the first letter of each word is uppercase, and the remaining letters are lowercase.

Example 2:

Input: title = "First leTTeR of EACH Word"
Output: "First Letter of Each Word"
Explanation:
The word "of" has length 2, so it is all lowercase.
The remaining words have a length of at least 3, so the first letter of each remaining word is uppercase, and the remaining letters are lowercase.

Example 3:

Input: title = "i lOve leetcode"
Output: "i Love Leetcode"
Explanation:
The word "i" has length 1, so it is lowercase.
The remaining words have a length of at least 3, so the first letter of each remaining word is uppercase, and the remaining letters are lowercase.

Constraints:

1 <= title.length <= 100
title consists of words separated by a single space without any leading or trailing spaces.
Each word consists of uppercase and lowercase English letters and is non-empty.
```

## Observations

1. **Word Length Rules**: The capitalization rules depend on word length:
   - Words with 1-2 letters: all lowercase
   - Words with 3+ letters: first letter uppercase, rest lowercase

2. **Input Format**: The input is a string with words separated by single spaces, no leading/trailing spaces

3. **Case Handling**: We need to handle mixed case input and normalize it according to the rules

4. **String Manipulation**: We need to split the string, process each word individually, then rejoin

## Solution

1. **Split the string**: Use `title.split()` to break the input into individual words
2. **Process each word**: Iterate through each word and apply the capitalization rules:
   - If word length ≤ 2: convert entire word to lowercase using `.lower()`
   - If word length > 2: use `.capitalize()` which makes first letter uppercase and rest lowercase
3. **Rejoin words**: Use `" ".join(words)` to combine the processed words back into a single string

**Time Complexity**: O(n) where n is the length of the input string
**Space Complexity**: O(n) for storing the split words array

**Key Insights:**
- The `.capitalize()` method is perfect for words ≥3 letters as it handles both the first letter capitalization and lowercasing the rest
- The `.lower()` method handles short words (1-2 letters) by making everything lowercase
- Using `split()` and `join()` is a clean way to process words individually while maintaining proper spacing

# Tags
String Manipulation, Array Processing

