## Problem

https://leetcode.com/problems/string-compression-ii/description

Run-length encoding is a string compression method that works by replacing consecutive identical characters (repeated 2 or more times) with the concatenation of the character and the number marking the count of the characters (length of the run). For example, to compress the string `"aabccc"` we replace `"aa"` by `"a2"` and replace `"ccc"` by `"c3"`. Thus the compressed string becomes `"a2bc3"`.

Notice that in this problem, we are **not** adding `'1'` after single characters.

Given a string `s` and an integer `k`, delete **at most** `k` characters from `s` such that the run-length encoded version of `s` has **minimum length**.

Return the minimum length of the run-length encoded version of `s` after deleting at most `k` characters.

**Example 1:**
```
Input: s = "aaabcccd", k = 2
Output: 4
Explanation: Compressing s without deleting anything gives "a3bc3d" of length 6.
Deleting 'b' and 'd' leaves "aaaccc", which compresses to "a3c3" of length 4.
```

**Example 2:**
```
Input: s = "aabbaa", k = 2
Output: 2
Explanation: Deleting both 'b' characters leaves "aaaa", which compresses to "a4" of length 2.
```

**Example 3:**
```
Input: s = "aaaaaaaaaaa", k = 0
Output: 3
Explanation: k = 0, no deletions allowed. The compressed string is "a11" of length 3.
```

**Constraints:**
- `1 <= s.length <= 100`
- `0 <= k <= s.length`
- `s` contains only lowercase English letters.

## Observations

- **Run-length encoded length** of a run of `l` identical characters contributes:
  - `0` if `l == 0`
  - `1` if `l == 1` (just the character, no count)
  - `2` if `2 <= l <= 9` (character + 1-digit count)
  - `3` if `10 <= l <= 99` (character + 2-digit count)
  - `4` if `l == 100` (character + 3-digit count, max possible since `|s| <= 100`)

- At each position we face a **binary choice**: delete the current character (use one of our `k` deletions) or keep it and start building a run.

- When we decide to keep `s[i]`, we can greedily **delete dissimilar characters** that appear between positions `i` and the end of the run, as long as we have remaining deletions. This maximizes the length of the current run, potentially reducing the encoded digit count.

- The key insight is: for a fixed starting index `i` and remaining deletions `cnt`, we scan forward and track:
  - `same`: how many characters equal to `s[i]` we've seen so far (kept characters).
  - `delete`: how many characters **not** equal to `s[i]` we've encountered (candidates to delete to extend the run).
  - Once `delete > cnt`, we must stop extending the current run.

- This naturally lends itself to **top-down DP with memoization** on the state `(i, cnt)`:
  - `i` — the current index we're processing.
  - `cnt` — the number of deletions remaining.
  - Total states: `O(n^2)`, transitions: `O(n)`, overall **`O(n^3)`** time.

- **Base cases:**
  - If `cnt < 0`: invalid state, return `∞`.
  - If `i >= n` or the remaining characters `n - i` are all deletable (`n - i <= cnt`): return `0`.

## Solution

```python
class Solution:
    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)

        def parse_len(l: int) -> int:
            """Returns the encoded length contributed by a run of l identical characters."""
            if l <= 0:
                return 0
            if l == 1:
                return 1    # just the character
            if l < 10:
                return 2    # character + 1-digit count
            if l < 100:
                return 3    # character + 2-digit count
            return 4        # character + 3-digit count (l == 100)

        mem = {}
        def F(i: int, cnt: int) -> int:
            """Minimum encoded length starting from index i with cnt deletions remaining."""
            if cnt < 0:
                return float('inf')
            if i >= n or n - i <= cnt:
                # Either past the string, or all remaining characters can be deleted
                return 0
            if (i, cnt) in mem:
                return mem[(i, cnt)]

            # Option 1: delete s[i], spend one deletion
            res = F(i + 1, cnt - 1)

            # Option 2: keep s[i], build the longest possible run starting at s[i]
            # Scan forward: keep characters equal to s[i], delete characters that differ
            same = 0    # count of s[i] characters kept in this run
            delete = 0  # count of non-s[i] characters deleted to extend the run
            for j in range(i, n):
                if s[j] == s[i]:
                    same += 1
                    # Cost = encoded length of this run + optimal cost for the rest
                    res = min(res, parse_len(same) + F(j + 1, cnt - delete))
                else:
                    delete += 1
                    if delete > cnt:
                        break   # can't delete any more, stop extending

            mem[(i, cnt)] = res
            return res

        return F(0, k)
```

**Walkthrough of Example 1** (`s = "aaabcccd"`, `k = 2`):
- `F(0, 2)`: Keep `'a'` at index 0. Scanning forward, `same` grows to 3 (indices 0–2). `'b'` at index 3 costs 1 deletion (`delete=1`). `'c'` at index 4 is different, `delete=2` which equals `cnt`, so we stop.
  - Best sub-choice: run of `a3` (cost 2) + `F(3, 2)` (handling `"bcccd"` with 2 deletions).
  - `F(3, 2)` deletes `'b'` and `'d'`, leaving `"ccc"` → `c3` (cost 2). Total = 4. ✓

# Tags

`Dynamic Programming` `Memoization` `String` `Hard`
