## Problem

https://leetcode.com/problems/construct-k-palindrome-strings/description/

Given a string `s` and an integer `k`, return `true` if you can use **all** the characters in `s` to construct exactly `k` non-empty palindrome strings, or `false` otherwise.

**Examples:**
- `s = "annabelle"`, `k = 2` → `true` (e.g. `"anna"` + `"elble"`)
- `s = "leetcode"`, `k = 3` → `false`
- `s = "true"`, `k = 4` → `true` (each character is its own palindrome)

**Constraints:**
- `1 <= s.length <= 10^5`
- `s` consists of lowercase English letters.
- `1 <= k <= 10^5`

---

## Observations

1. **Every character must be used.** We cannot discard any character — all of `s` must be distributed across exactly `k` palindromes.

2. **Minimum number of palindromes needed — odd frequency characters.**
   In a palindrome, at most **one** character can appear an odd number of times (the center character). So every character with an odd frequency **must** be the center of its own palindrome. This means:
   > `count_odd_freq` = number of characters with odd frequency = **minimum number of palindromes** required.

   If `count_odd_freq > k`, it is impossible — we don't have enough palindromes to absorb all odd-frequency characters as centers.

3. **Maximum number of palindromes possible — length of s.**
   Each palindrome must be non-empty, so we can have at most `len(s)` palindromes (one character each).

   If `k > len(s)`, it is impossible — we don't have enough characters to fill `k` non-empty strings.

4. **Any value of `k` between `count_odd_freq` and `len(s)` is achievable.**
   - We can always split even-frequency pairs across palindromes freely.
   - We can always "break off" a single character into its own palindrome to increase the count.
   - So the feasible range is: `count_odd_freq <= k <= len(s)`.

---

## Solution Explanation

```python
from collections import defaultdict

class Solution:
    def canConstruct(self, s: str, k: int) -> bool:
        # Upper bound: can't form more palindromes than characters available
        if k > len(s):
            return False
        
        # Count character frequencies
        f = defaultdict(int)
        for c in s:
            f[c] += 1
        
        # Count characters with odd frequency
        count_odd_freq = 0
        for c in f:
            count_odd_freq += (f[c] & 1)  # f[c] & 1 == 1 if odd, 0 if even
        
        # Lower bound: need at least one palindrome per odd-frequency character
        return count_odd_freq <= k
```

**Step-by-step:**

1. **Guard `k > len(s)`:** If we need more palindromes than characters, immediately return `false`.

2. **Compute frequency map:** Count how many times each character appears in `s`.

3. **Count odd frequencies:** Use `f[c] & 1` (bitwise AND) to check if a frequency is odd. Sum these up into `count_odd_freq`.

4. **Final check `count_odd_freq <= k`:** Combined with the guard in step 1, this ensures `count_odd_freq <= k <= len(s)`, which is exactly the feasible range.

**Complexity:**
- Time: `O(n)` — one pass to build the frequency map, one pass over at most 26 characters.
- Space: `O(1)` — the frequency map holds at most 26 entries (lowercase English letters).
