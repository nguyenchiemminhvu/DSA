## Problem

https://leetcode.com/problems/most-common-word/

```
Given a string paragraph and a string array of the banned words banned, return the most frequent word that is not banned. It is guaranteed there is at least one word that is not banned, and that the answer is unique.

The words in paragraph are case-insensitive and the answer should be returned in lowercase.

Note that words can not contain punctuation symbols.

Example 1:

Input: paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.", banned = ["hit"]
Output: "ball"
Explanation: 
"hit" occurs 3 times, but it is a banned word.
"ball" occurs twice (and no other word does), so it is the most frequent non-banned word in the paragraph. 
Note that words in the paragraph are not case sensitive,
that punctuation is ignored (even if adjacent to words, such as "ball,"), 
and that "hit" isn't the answer even though it occurs more because it is banned.

Example 2:

Input: paragraph = "a.", banned = []
Output: "a"

Constraints:

1 <= paragraph.length <= 1000
paragraph consists of English letters, space ' ', or one of the symbols: "!?',;.".
0 <= banned.length <= 100
1 <= banned[i].length <= 10
banned[i] consists of only lowercase English letters.
```

## Observations

1. **Case Insensitivity**: Words need to be normalized to lowercase for comparison since "Ball" and "ball" should be treated as the same word.

2. **Punctuation Handling**: The paragraph contains punctuation marks (`!?',;.`) that need to be removed/ignored when extracting words.

3. **Banned Words**: We need to exclude words that appear in the banned list from our frequency count.

4. **Frequency Tracking**: We need to count occurrences of each valid word and find the one with maximum frequency.

5. **Guaranteed Solution**: The problem guarantees there's at least one non-banned word and the answer is unique, so we don't need to handle edge cases for ties or empty results.

6. **Empty Strings**: After splitting, we might get empty strings that should be ignored.

## Solution

The solution uses a straightforward approach with the following steps:

### Algorithm:
1. **Convert banned list to set**: `banned = set(banned)` - O(1) lookup time instead of O(n)
2. **Split and normalize**: Use regex `re.split(r"[!?',; \.]+", paragraph)` to split on punctuation and spaces, then convert to lowercase
3. **Count frequencies**: Iterate through words, skip banned ones, and maintain frequency count
4. **Track maximum**: Keep track of the current maximum frequency and corresponding word during iteration

### Key Components:

**Regex Pattern**: `r"[!?',; \.]+"` 
- Matches one or more occurrences of punctuation and spaces
- The `+` ensures consecutive punctuation is treated as one delimiter
- Escaping the dot `\.` to match literal periods

**Frequency Tracking**:
```python
freq[word] = freq.get(word, 0) + 1
if freq[word] > cur_max:
    cur_max = freq[word]
    cur_str = word
```
- Uses `dict.get()` with default value 0 for clean frequency increment
- Updates maximum frequency and word in the same pass

### Time Complexity: O(n + m)
- n = length of paragraph (for splitting and processing)
- m = length of banned list (for set conversion)

### Space Complexity: O(n + m)
- n = space for storing words and frequency map
- m = space for banned set

### Example Walkthrough:
For `paragraph = "Bob hit a ball, the hit BALL flew far after it was hit."` and `banned = ["hit"]`:

1. After splitting and lowercasing: `["bob", "hit", "a", "ball", "", "the", "hit", "ball", "flew", "far", "after", "it", "was", "hit", ""]`
2. Filter out banned "hit" and empty strings
3. Count frequencies: `{"bob": 1, "a": 1, "ball": 2, "the": 1, "flew": 1, "far": 1, "after": 1, "it": 1, "was": 1}`
4. "ball" has maximum frequency of 2

# Tags

String Processing, Hash Map, Regular Expressions, Frequency Counting

