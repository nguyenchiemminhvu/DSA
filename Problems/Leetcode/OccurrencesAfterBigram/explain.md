## Problem

https://leetcode.com/problems/occurrences-after-bigram/description/

```
Given two strings first and second, consider occurrences in some text of the form "first second third", 
where second comes immediately after first, and third comes immediately after second.

Return an array of all the words third for each occurrence of "first second third".

Example 1:
Input: text = "alice is a good girl she is a good student", first = "a", second = "good"
Output: ["girl","student"]

Example 2:
Input: text = "we will we will rock you", first = "we", second = "will"
Output: ["we","rock"]

Constraints:
- 1 <= text.length <= 1000
- text consists of lowercase English letters and spaces.
- All the words in text are separated by a single space.
- 1 <= first.length, second.length <= 10
- first and second consist of lowercase English letters.
- text will not have any leading or trailing spaces.
```

## Observations

- We need to find patterns of three consecutive words where the first two match the given `first` and `second` strings
- The problem is essentially pattern matching in a sequence of words
- We need to return the third word in each matching pattern
- Since words are separated by single spaces, we can split the text into an array of words
- We need to check bounds carefully to avoid index out of range errors

## Solution

**Approach: Linear Scan with Pattern Matching**

The solution uses a straightforward approach:

1. **Split the text**: Convert the text into an array of words using `split()`, which splits by whitespace
2. **Iterate through words**: Loop through each word with index `i`
3. **Check pattern**: For each position, verify:
   - Current word matches `first`
   - Next word (i+1) exists and matches `second`
   - Word after that (i+2) exists (this is the word we want to collect)
4. **Collect results**: If all conditions are met, append the third word to the result array

**Time Complexity**: O(n) where n is the number of words in the text. We iterate through the array once.

**Space Complexity**: O(n) for storing the split words array and the result array.

**Key Points:**
- The condition `i + 1 < len(arr)` ensures we don't access out of bounds when checking the second word
- The condition `i + 2 < len(arr)` ensures the third word exists before we try to append it
- The and operator uses short-circuit evaluation, so bounds are checked before array access

# Tags
#array #string #pattern-matching #two-pointer

