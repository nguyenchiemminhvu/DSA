## Problem

https://leetcode.com/problems/count-the-number-of-special-characters-ii/description

You are given a string `word`. A letter `c` is called **special** if it appears both in lowercase and uppercase in `word`, **and every lowercase occurrence of `c` appears before the first uppercase occurrence of `c`**.

Return the number of special letters in `word`.

**Example 1:**
- Input: `word = "aaAbcBC"`
- Output: `3`
- Explanation: The special characters are `'a'`, `'b'`, and `'c'`.

**Example 2:**
- Input: `word = "abc"`
- Output: `0`
- Explanation: There are no special characters in `word`.

**Example 3:**
- Input: `word = "AbBCab"`
- Output: `0`
- Explanation: There are no special characters in `word`.

**Constraints:**
- `1 <= word.length <= 2 * 10^5`
- `word` consists of only lowercase and uppercase English letters.

## Observations

- A character `c` is special only if **both** `c` (lowercase) and `C` (uppercase) exist in the string.
- The condition is stricter than part I: **every** lowercase occurrence must come before the **first** uppercase occurrence — not just at least one.
- This means we need to track the **last** index of any lowercase `c` and the **first** index of any uppercase `C`.
- If `last_lower_idx[c] < first_upper_idx[c]`, then all lowercase `c`s appear before all uppercase `C`s (since any lowercase after the last one would have a higher index).
- Iterating from right to left is a clean way to naturally capture `first_upper_idx` (the rightmost index seen first becomes the earliest as we move left) — actually, since we scan right to left, the **last assignment** for an uppercase letter gives us the **leftmost** (first) uppercase index. For lowercase, we only record it if not yet seen, giving us the **rightmost** (last) lowercase index.

## Solution

Scan the string from **right to left**:
- For each uppercase letter `C`, keep updating `first_upper_idx[c]` — scanning right-to-left means the final stored value is the **leftmost (first) uppercase** index.
- For each lowercase letter `c`, record `last_lower_idx[c]` only on **first encounter** (right-to-left), so the stored value is the **rightmost (last) lowercase** index.

Then, for each letter in the alphabet, check if:
1. It has both a lowercase and uppercase occurrence.
2. `last_lower_idx[c] < first_upper_idx[c]` — meaning all lowercase occurrences are guaranteed to be before the first uppercase.

```python
import string

class Solution:
    def numberOfSpecialChars(self, s: str) -> int:
        n = len(s)

        first_upper_idx = {}
        last_lower_idx = {}
        for i in range(n - 1, -1, -1):
            c = s[i]
            if c.isupper():
                first_upper_idx[c.lower()] = i      # overwrite -> ends up with leftmost (first) uppercase index
            elif c not in last_lower_idx:
                last_lower_idx[c] = i               # first encounter right-to-left -> rightmost (last) lowercase index
        
        res = 0
        for c in string.ascii_lowercase:
            if c in first_upper_idx and c in last_lower_idx and last_lower_idx[c] < first_upper_idx[c]:
                res += 1
        return res
```

**Complexity:**
- Time: $O(n + 26) = O(n)$ — one pass over the string, one pass over the alphabet.
- Space: $O(26) = O(1)$ — at most 26 entries in each dictionary.

# Tags
`Hash Map` `String`

