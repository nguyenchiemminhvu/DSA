## Problem

https://leetcode.com/problems/largest-substring-between-two-equal-characters/

```
Given a string s, return the length of the longest substring between two equal characters, excluding the two characters. If there is no such substring return -1.

A substring is a contiguous sequence of characters within a string.

Example 1:

Input: s = "aa"
Output: 0
Explanation: The optimal substring here is an empty substring between the two 'a's.

Example 2:

Input: s = "abca"
Output: 2
Explanation: The optimal substring here is "bc".

Example 3:

Input: s = "cbzxy"
Output: -1
Explanation: There are no characters that appear twice in s.

Constraints:

1 <= s.length <= 300
s contains only lowercase English letters.
```

## Observations

1. **Two-pointer approach per character**: For each character, we need to track the first and last occurrence positions.
2. **Maximum distance calculation**: The length of substring between two equal characters is `right_index - left_index - 1`.
3. **Edge cases**: 
   - If a character appears only once, there's no substring between equal characters
   - If no character appears more than once, return -1
4. **Optimization**: Since we only have lowercase English letters (26 characters), we can use a fixed-size array to track positions.

## Solution

1. **Initialize tracking array**: Create `prefix` array with 26 pairs `[-1, -1]` to track first and last occurrence of each letter.

2. **Record positions**: 
   - For each character in the string, convert it to index (0-25) using `ord(c) - ord('a')`
   - If it's the first occurrence (`prefix[ip][0] == -1`), store the index in first position
   - Otherwise, update the last occurrence position

3. **Find maximum length**:
   - Iterate through all 26 possible characters
   - For characters that appear at least twice (`right > left`), calculate substring length as `right - left - 1`
   - Keep track of the maximum length found

**Time Complexity**: O(n) where n is the length of string
**Space Complexity**: O(1) since we use fixed array of size 26

**Key Insight**: The substring length between two equal characters at positions `i` and `j` is `j - i - 1` because we exclude the characters at positions `i` and `j`.

# Tags

