## Problem

https://leetcode.com/problems/sum-of-beauty-of-all-substrings/

The **beauty** of a string is the difference between the frequency of its most frequent character and its least frequent character.

Given a string `s`, return the sum of beauty of **all** its substrings.

**Example:**
- `s = "aabcb"` → output `5`
  - Substrings with non-zero beauty: `["aab","aabc","aabcb","abcb","bcb"]`, each with beauty `1`.

**Constraints:** `1 ≤ len(s) ≤ 500`, lowercase English letters only.

---

## Approach: Prefix Frequency Array

### Key Idea

To compute the beauty of every substring `s[l..r]` efficiently, we need quick access to character frequencies in any range. A **prefix frequency array** gives us this in O(26) per query instead of O(n).

### Prefix Frequency Array

Build `prefix_freq` where `prefix_freq[i][c]` = number of occurrences of character `c` in `s[0..i-1]`.

```
s = "aabcb"
       a  b  c  ...
[0]:  [0, 0, 0, ...]   (empty prefix)
[1]:  [1, 0, 0, ...]   after 'a'
[2]:  [2, 0, 0, ...]   after 'a'
[3]:  [2, 1, 0, ...]   after 'b'
[4]:  [2, 1, 1, ...]   after 'c'
[5]:  [2, 2, 1, ...]   after 'b'
```

Frequency of character `c` in substring `s[l..r]` (0-indexed, inclusive):
$$\text{freq}[c] = \text{prefix\_freq}[r+1][c] - \text{prefix\_freq}[l][c]$$

### Algorithm

1. Build the prefix frequency table in O(26·n).
2. Enumerate all O(n²) substrings `(l, r)`.
3. For each substring, compute the 26 character frequencies via prefix subtraction.
4. Scan the 26 frequencies to find `max` (most frequent) and `min` (least frequent, among characters that appear).
5. Add `max - min` to the result.

### Complexity

| | Value |
|---|---|
| Time | O(n² · 26) |
| Space | O(n · 26) |

Given n ≤ 500, this is at most ~3.25M operations — well within limits.

### Code Walkthrough

```python
class Solution:
    def beautySum(self, s: str) -> int:
        n = len(s)

        # Step 1: Build prefix frequency table
        # prefix_freq[i] holds cumulative char counts for s[0..i-1]
        prefix_freq = [[0] * 26]
        f = [0] * 26
        for i in range(n):
            f[ord(s[i]) - ord('a')] += 1
            prefix_freq.append(f[:])   # snapshot after including s[i]

        res = 0
        for l in range(n):
            for r in range(l, n):
                # Step 2: Compute frequencies for s[l..r] via prefix subtraction
                f = prefix_freq[r + 1][:]
                for i in range(26):
                    f[i] -= prefix_freq[l][i]

                # Step 3: Find max and min frequency (only among present chars)
                mi, ma = n, 0
                for i in range(26):
                    if f[i]:                        # character appears in s[l..r]
                        mi = min(mi, f[i])
                        ma = max(ma, f[i])

                res += ma - mi   # beauty of this substring
        return res
```

### Trace on `s = "aabcb"`

| Substring | Frequencies | max | min | beauty |
|-----------|-------------|-----|-----|--------|
| `"a"` | a:1 | 1 | 1 | 0 |
| `"aa"` | a:2 | 2 | 2 | 0 |
| `"aab"` | a:2, b:1 | 2 | 1 | **1** |
| `"aabc"` | a:2, b:1, c:1 | 2 | 1 | **1** |
| `"aabcb"` | a:2, b:2, c:1 | 2 | 1 | **1** |
| `"ab"` | a:1, b:1 | 1 | 1 | 0 |
| `"abc"` | a:1, b:1, c:1 | 1 | 1 | 0 |
| `"abcb"` | a:1, b:2, c:1 | 2 | 1 | **1** |
| `"b"` | b:1 | 1 | 1 | 0 |
| `"bc"` | b:1, c:1 | 1 | 1 | 0 |
| `"bcb"` | b:2, c:1 | 2 | 1 | **1** |
| `"c"` | c:1 | 1 | 1 | 0 |
| `"cb"` | c:1, b:1 | 1 | 1 | 0 |
| `"b"` | b:1 | 1 | 1 | 0 |

Total: **5** ✓
