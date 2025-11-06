## Problem

https://leetcode.com/problems/find-common-characters/description/

```
Given a string array words, return an array of all characters that show up in all strings within the words (including duplicates). You may return the answer in any order.

Example 1:

Input: words = ["bella","label","roller"]
Output: ["e","l","l"]

Example 2:

Input: words = ["cool","lock","cook"]
Output: ["c","o"]

Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consists of lowercase English letters.
```

## Observations

1. **Problem Understanding**: We need to find characters that appear in ALL strings, including their duplicates. If a character appears multiple times in all strings, we need to include it the minimum number of times it appears across all strings.

2. **Key Insights**:
   - For each character (a-z), we need to track its frequency in each word
   - A character is "common" only if it appears in ALL words
   - The number of times we include a common character in the result is the minimum frequency across all words

3. **Example Analysis**:
   - `["bella","label","roller"]`: 
     - 'e' appears 1 time in each word → include 1 'e'
     - 'l' appears 2,2,2 times respectively → include 2 'l's
   - `["cool","lock","cook"]`:
     - 'c' appears 1,0,1 times → not common (missing in "lock")
     - 'o' appears 2,1,2 times → include 1 'o' (minimum)

## Solution

1. **Data Structure**: 
   - `f[idx]` is a dictionary where `f[idx][i]` represents the count of character `idx` in word `i`
   - We use 26 dictionaries, one for each lowercase letter

2. **Frequency Counting**:
   - For each word `i` and each character `c` in that word
   - Convert character to index: `idx = ord(c) - ord('a')`
   - Increment the count: `f[idx][i] += 1`

3. **Finding Common Characters**:
   - For each character index `idx` (0-25 representing a-z)
   - Check if `len(f[idx].keys()) == n` (appears in all n words)
   - If yes, add `min(f[idx].values())` copies to result (minimum frequency)

**Time Complexity**: O(N × M) where N is number of words and M is average word length
**Space Complexity**: O(N) for storing frequency data for each word

**Alternative Approach**: Use `Counter` from collections module for cleaner code:
```python
from collections import Counter

class Solution:
    def commonChars(self, words: List[str]) -> List[str]:
        common = Counter(words[0])
        for word in words[1:]:
            common &= Counter(word)  # Intersection with minimum counts
        return list(common.elements())
```

# Tags

- Array
- Hash Table
- String
- Counting

