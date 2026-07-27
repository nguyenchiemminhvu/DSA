## Problem

https://leetcode.com/problems/append-characters-to-string-to-make-subsequence/description/

Given two strings `s` and `t` consisting of only lowercase English letters, return the minimum number of characters that need to be appended to the end of `s` so that `t` becomes a **subsequence** of `s`.

A **subsequence** is a string derived from another string by deleting some or no characters without changing the order of the remaining characters.

**Example 1:**
- Input: `s = "coaching"`, `t = "coding"`
- Output: `4`
- Explanation: Append `"ding"` → `s = "coachingding"`, now `t` is a subsequence.

**Example 2:**
- Input: `s = "abcde"`, `t = "a"`
- Output: `0`
- Explanation: `t` is already a subsequence of `s`.

**Example 3:**
- Input: `s = "z"`, `t = "abcde"`
- Output: `5`
- Explanation: Append all 5 characters of `t`.

**Constraints:**
- `1 <= s.length, t.length <= 10^5`
- `s` and `t` consist only of lowercase English letters.

---

## Ideas

### Greedy Two-Pointer — O(n + m) time, O(1) space

Use a pointer `j` to track how far we've matched into `t` as we scan `s` left-to-right.
For each character `s[i]`, if it equals `t[j]`, advance `j`.
After the scan, `j` is the number of characters of `t` already matched as a subsequence in `s`.
The answer is `t.length - j` — the remaining unmatched suffix of `t` must be appended.

```
j = 0
for i in range(len(s)):
    if j < len(t) and s[i] == t[j]:
        j += 1
return len(t) - j
```

- No appending needed if `t` is already fully matched (`j == len(t)` → return 0).
- In the worst case (no characters match), we append all of `t`.
