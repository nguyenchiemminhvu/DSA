## Problem

https://leetcode.com/problems/minimum-window-substring/

```
Given two strings s and t of lengths m and n respectively, return the minimum window
substring of s such that every character in t (including duplicates) is included in
the window. If there is no such substring, return the empty string "".

Example 1:
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"

Example 2:
Input: s = "a", t = "a"
Output: "a"

Example 3:
Input: s = "a", t = "aa"
Output: ""

Constraints:
1 <= m, n <= 10^5
s and t consist of uppercase and lowercase English letters.
```

## Observations

- We need a **contiguous** substring of `s` that covers every character of `t`, counting duplicates. If `t = "aa"`, the window must hold at least two `a`s.
- The brute-force approach enumerates all O(m²) substrings and checks each one — O(m² · n) overall, far too slow.
- Key insight: if a window `[l, r]` is already valid, moving `r` further right keeps it valid but potentially makes it longer. To find the *minimum*, we should instead shrink from the left until it just becomes invalid, then record the window size before shrinking.
- This "expand right, shrink left" pattern is the classic **sliding window**.
- We only need to track **character frequencies**: a frequency map for `t` (`ft`) tells us what we need, and a frequency map for the current window (`fs`) tells us what we have. The window is valid when `fs[c] >= ft[c]` for every character `c` in `t`.
- Because all characters are ASCII letters, the frequency maps hold at most 52 distinct keys — bounded by the alphabet size |Σ|.

## Solution

```python
from collections import defaultdict

class Solution:
    def minWindow(self, s: str, t: str) -> str:
        m, n = len(s), len(t)

        # Check whether the current window frequency map (d1)
        # satisfies every requirement in the target frequency map (d2).
        def compare_defaultdicts(d1, d2):
            for k, v in d2.items():
                if k not in d1 or d1[k] < v:
                    return False
            return True

        # Build frequency map for t.
        ft = defaultdict(int)
        for c in t:
            ft[c] += 1

        l = 0
        fs = defaultdict(int)          # frequency map for the current window
        res = [-1, m]                  # sentinel: res[1]-res[0] = m+1 > any valid window

        for r in range(m):
            fs[s[r]] += 1              # expand window to the right

            # While the window is valid, try to shrink it from the left.
            while compare_defaultdicts(fs, ft):
                # r - l is the current window length minus 1 (indices are inclusive).
                # res stores [start, end) so res[1]-res[0] is the length.
                if r - l < res[1] - res[0]:
                    res = [l, r + 1]
                # Remove leftmost character and move l forward.
                fs[s[l]] -= 1
                if fs[s[l]] <= 0:
                    fs.pop(s[l])       # keep fs tidy; avoids stale zero entries
                l += 1

        # res[1] - res[0] stays m+1 if no valid window was ever found.
        return '' if res[1] - res[0] > m else s[res[0]:res[1]]
```

**Step-by-step walkthrough** with `s = "ADOBECODEBANC"`, `t = "ABC"`:

| r  | s[r] | window        | fs covers ft? | action             | best res   |
|----|------|---------------|---------------|--------------------|------------|
| 0  | A    | A             | No            | expand             | —          |
| 1  | D    | AD            | No            | expand             | —          |
| 2  | O    | ADO           | No            | expand             | —          |
| 3  | B    | ADOB          | No            | expand             | —          |
| 4  | E    | ADOBE         | No            | expand             | —          |
| 5  | C    | ADOBEC        | **Yes**       | shrink l→1, record | [0,6]      |
|    |      | DOBEC         | No            | stop shrinking     |            |
| 6  | O    | DOBECO        | No            | expand             |            |
| 7  | D    |DOBECOD       | No            | expand             |            |
| 8  | E    | DOBECODE      | No            | expand             |            |
| 9  | B    | DOBECODEB     | No            | expand             |            |
| 10 | A    | DOBECÓDEBA    | **Yes**       | shrink l→…, record | [0,6]      |
|    |      | …             | …             | keep shrinking     |            |
| 11 | N    | …             | No at some pt | expand             |            |
| 12 | C    | BANC          | **Yes**       | shrink, record     | **[9,13]** |

Final answer: `s[9:13]` = `"BANC"` ✓

**Sentinel trick:** `res = [-1, m]` gives initial span `m - (-1) = m + 1`, which is larger than the longest possible valid window (length `m`). So `res[1] - res[0] > m` is a clean "not found" check.

**Complexity:**

| | |
|---|---|
| Time | O(m · \|Σ\|) — each of the m right-pointer steps may call `compare_defaultdicts`, which iterates over the ≤ 52 keys of `ft`. The left pointer also moves at most m times total. |
| Space | O(\|Σ\|) for `ft` and `fs` |

> **Follow-up O(m + n) approach:** Replace `compare_defaultdicts` with two counters `have` and `need`. Increment `have` when `fs[c]` first reaches `ft[c]`; decrement it when shrinking causes `fs[c]` to drop below `ft[c]`. The window is valid iff `have == need`. Each pointer moves at most m times and each check is O(1), giving true O(m + n).

## Tags

string, hash table, sliding window, two pointers
