## Problem

https://leetcode.com/problems/split-strings-by-separator/

```
Given an array of strings words and a character separator, split each string in words by separator.

Return an array of strings containing the new strings formed after the splits, excluding empty strings.

Notes

separator is used to determine where the split should occur, but it is not included as part of the resulting strings.
A split may result in more than two strings.
The resulting strings must maintain the same order as they were initially given.

Example 1:

Input: words = ["one.two.three","four.five","six"], separator = "."
Output: ["one","two","three","four","five","six"]
Explanation: In this example we split as follows:

"one.two.three" splits into "one", "two", "three"
"four.five" splits into "four", "five"
"six" splits into "six" 

Hence, the resulting array is ["one","two","three","four","five","six"].

Example 2:

Input: words = ["$easy$","$problem$"], separator = "$"
Output: ["easy","problem"]
Explanation: In this example we split as follows: 

"$easy$" splits into "easy" (excluding empty strings)
"$problem$" splits into "problem" (excluding empty strings)

Hence, the resulting array is ["easy","problem"].

Example 3:

Input: words = ["|||"], separator = "|"
Output: []
Explanation: In this example the resulting split of "|||" will contain only empty strings, so we return an empty array []. 

Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 20
characters in words[i] are either lowercase English letters or characters from the string ".,|$#@" (excluding the quotes)
separator is a character from the string ".,|$#@" (excluding the quotes)
```

## Observations

1. **Problem Requirements:**
   - Split each string in the input array by the given separator
   - Exclude empty strings from the result
   - Maintain the original order of strings
   - The separator itself should not appear in the result

2. **Key Insights:**
   - We need to process each word individually
   - Python's built-in `split()` method handles the splitting logic
   - `split(sep)` can produce empty strings when there are consecutive separators or separators at the beginning/end
   - We need to filter out these empty strings
   - The order must be preserved as we process words sequentially

3. **Edge Cases:**
   - Words that consist only of separators (like "|||") should contribute nothing to the result
   - Single characters that aren't separators should remain as-is
   - Multiple consecutive separators should be treated as producing empty strings between them

## Solution

```python
class Solution:
    def splitWordsBySeparator(self, words: List[str], sep: str) -> List[str]:
        res = []
        for word in words:
            res.extend(filter(None, word.split(sep)))
        return res
```

**Algorithm Explanation:**

1. **Initialize Result:** Create an empty list `res` to store the final result.

2. **Process Each Word:** Iterate through each word in the input array.

3. **Split and Filter:** For each word:
   - `word.split(sep)` splits the word by the separator, returning a list of substrings
   - `filter(None, ...)` removes all falsy values (empty strings) from the split result
   - `res.extend(...)` adds all filtered substrings to the result list

4. **Return Result:** Return the accumulated list of non-empty substrings.

**Why This Works:**

- `split(sep)` naturally handles all the splitting logic and edge cases
- `filter(None, ...)` elegantly removes empty strings since empty strings are falsy in Python
- `extend()` maintains the order by adding elements sequentially
- The solution is both concise and efficient

**Time Complexity:** O(n × m) where n is the number of words and m is the average length of each word
**Space Complexity:** O(k) where k is the total number of characters in all resulting substrings

# Tags

`Array` `String` `String Manipulation`

