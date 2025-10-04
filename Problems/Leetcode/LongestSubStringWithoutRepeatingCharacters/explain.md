## Problem

https://leetcode.com/problems/longest-substring-without-repeating-characters/

```
Given a string s, find the length of the longest substring without duplicate characters.

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.

Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.
```

## Observations

- The problem asks for the length of the longest substring without repeating characters.
- A substring is a contiguous sequence of characters within the string.
- The brute-force approach would check all substrings, but this is inefficient for large strings.
- Efficient solutions use a sliding window and a set or map to track seen characters.

## Solution

We use a sliding window approach with two pointers (`left` and `right`) and a set to keep track of unique characters in the current window. As we iterate through the string with the `right` pointer:
- If the character at `right` is not in the set, we expand the window and update the maximum length.
- If the character is already in the set, we shrink the window from the left until the duplicate is removed.
- This ensures each character is processed at most twice, resulting in $O(n)$ time complexity.

## Tags

array, string, hash table, two pointers