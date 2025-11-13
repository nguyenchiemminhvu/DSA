## Problem

https://leetcode.com/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/description/

```
Given a sentence that consists of some words separated by a single space, and a searchWord, check if searchWord is a prefix of any word in sentence.

Return the index of the word in sentence (1-indexed) where searchWord is a prefix of this word. If searchWord is a prefix of more than one word, return the index of the first word (minimum index). If there is no such word return -1.

A prefix of a string s is any leading contiguous substring of s.

Example 1:

Input: sentence = "i love eating burger", searchWord = "burg"
Output: 4
Explanation: "burg" is prefix of "burger" which is the 4th word in the sentence.
Example 2:

Input: sentence = "this problem is an easy problem", searchWord = "pro"
Output: 2
Explanation: "pro" is prefix of "problem" which is the 2nd and the 6th word in the sentence, but we return 2 as it's the minimal index.
Example 3:

Input: sentence = "i am tired", searchWord = "you"
Output: -1
Explanation: "you" is not a prefix of any word in the sentence.

Constraints:

1 <= sentence.length <= 100
1 <= searchWord.length <= 10
sentence consists of lowercase English letters and spaces.
searchWord consists of lowercase English letters.
```

## Observations

1. **Problem Understanding**: We need to find if a given `searchWord` is a prefix of any word in a sentence and return the 1-indexed position of the first such word.

2. **Key Requirements**:
   - Words are separated by single spaces
   - Return 1-indexed position (not 0-indexed)
   - If multiple words have the prefix, return the first occurrence
   - Return -1 if no word has the given prefix

3. **Input Constraints**:
   - Sentence length: 1-100 characters
   - SearchWord length: 1-10 characters  
   - Only lowercase letters and spaces
   - This means we don't need to worry about case sensitivity or special characters

4. **Edge Cases**:
   - Single word sentence
   - SearchWord longer than any word in sentence
   - SearchWord matches entire word (still counts as prefix)
   - Empty searchWord (not possible due to constraints)

## Solution

**Approach**: Simple Linear Search with String Prefix Check

**Algorithm**:
1. Split the sentence into individual words using `split()`
2. Iterate through each word with its index using `enumerate()`
3. For each word, check if it starts with the target string using `startswith()`
4. Return the 1-indexed position (i + 1) of the first matching word
5. If no word matches, return -1

**Time Complexity**: O(n × m) where n is the number of words and m is the average length of searchWord
- `split()` operation: O(n) where n is sentence length
- For each word: O(m) to check prefix where m is searchWord length
- In worst case, we check all words

**Space Complexity**: O(n) where n is the number of words (for storing the split words array)

**Example Trace**:
- Input: `sentence = "i love eating burger"`, `searchWord = "burg"`
- `words = ["i", "love", "eating", "burger"]`
- Check "i".startswith("burg") → False
- Check "love".startswith("burg") → False  
- Check "eating".startswith("burg") → False
- Check "burger".startswith("burg") → True → return 3 + 1 = 4

**Why This Works**:
- The `startswith()` method efficiently checks if a string begins with a given prefix
- `enumerate()` gives us both the word and its 0-indexed position
- Adding 1 converts to the required 1-indexed format
- Early return ensures we get the first occurrence

# Tags

#string-manipulation #prefix #linear-search #string-methods #easy

