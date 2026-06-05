## Problem

https://leetcode.com/problems/find-all-anagrams-in-a-string/description/

```
Given two strings s and p, return an array of all the start indices of p's anagrams in s.
You may return the answer in any order.

Example 1:
Input: s = "cbaebabacd", p = "abc"
Output: [0,6]
Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".

Example 2:
Input: s = "abab", p = "ab"
Output: [0,1,2]
Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

Constraints:
- 1 <= s.length, p.length <= 3 * 10^4
- s and p consist of lowercase English letters.
```

## Observations

1. **Anagram = identical character frequencies**: Two strings are anagrams of each other if and only if their character frequency arrays are identical. We don't need to sort or enumerate permutations — comparing two frequency arrays is sufficient.

2. **Fixed-size window**: Every anagram of `p` has exactly `len(p)` characters. This means we only need to examine substrings of `s` whose length equals `len(p)`, making this a **fixed-size sliding window** problem.

3. **Frequency array instead of hash map**: Because the input is restricted to lowercase English letters, a fixed array of 26 integers indexed by `ord(c) - ord('a')` is both more space-efficient and allows direct `==` comparison in O(26) = O(1).

4. **Incremental update**: Rather than recomputing the frequency array from scratch for every window position (which would be O(n · m)), we maintain it incrementally: add the new right character when the window expands, and remove the leftmost character when the window needs to shrink. Each step is O(1).

5. **Window size invariant**: The left pointer `l` moves only when the window exceeds `len(p)`. After the removal, `r - l + 1 == len(p)` holds exactly — this is the moment to compare the two frequency arrays.

## Solution

### Approach: Fixed-Size Sliding Window with Frequency Arrays

Pre-compute the frequency array `fp` for `p`, then slide a window of size `len(p)` across `s`, maintaining a live frequency array `fs` for the current window. Whenever the two arrays match, the window's start index is an anagram position.

### Algorithm

```python
class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:
        fp = [0] * 26
        for c in p:
            fp[ord(c) - ord('a')] += 1

        ns, np = len(s), len(p)

        res = []
        fs = [0] * 26
        l = 0
        for r in range(ns):
            # Expand window: include s[r]
            fs[ord(s[r]) - ord('a')] += 1

            # Shrink window if it exceeds the target size
            if r - l + 1 > np:
                fs[ord(s[l]) - ord('a')] -= 1
                l += 1

            # Window is exactly size np — check for anagram
            if r - l + 1 == np:
                if fp == fs:
                    res.append(l)

        return res
```

### Example Walkthrough (`s = "cbaebabacd"`, `p = "abc"`)

`fp = [1, 1, 1, 0, ...]` (counts for a, b, c)

| r | window   | fs (a,b,c) | fp == fs | res   |
|---|----------|------------|----------|-------|
| 0 | "c"      | [0,0,1]    | —        |       |
| 1 | "cb"     | [0,1,1]    | —        |       |
| 2 | "cba"    | [1,1,1]    | ✓        | [0]   |
| 3 | "bae"    | [1,1,0]    | ✗        | [0]   |
| 4 | "aeba"   | shrink → "aeb"  → [1,1,0] | ✗ | [0] |
| 5 | "ebab"   | shrink → "bab"  → [1,2,0] | ✗ | [0] |
| 6 | "baba"   | shrink → "aba"  → [2,1,0] | ✗ | [0] |
| 7 | "abac"   | shrink → "bac"  → [1,1,1] | ✓ | [0,6] |

### Complexity Analysis

- **Time Complexity**: O(n_s + n_p) — one O(n_p) pass to build `fp`, then one O(n_s) pass over `s`. Each window comparison is O(26) = O(1), so the total is linear.

- **Space Complexity**: O(1) — only two fixed-size arrays of 26 integers, regardless of input size.

### Why This Works

The sliding window guarantees every substring of length `np` in `s` is evaluated exactly once. The frequency array comparison in O(1) keeps the overall algorithm linear. Because we shrink the window before comparing, the invariant `r - l + 1 == np` is always maintained at the comparison point, ensuring we never check a window of the wrong size.

## Tags
`sliding-window` `two-pointers` `string` `hash-map`
