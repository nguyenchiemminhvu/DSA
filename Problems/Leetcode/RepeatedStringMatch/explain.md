## Problem

https://leetcode.com/problems/repeated-string-match/description

Given two strings `a` and `b`, return the **minimum number of times** you should repeat string `a` so that string `b` is a substring of it. If it is impossible for `b` to be a substring of `a` after repeating, return `-1`.

**Example 1:**
```
Input: a = "abcd", b = "cdabcdab"
Output: 3
Explanation: "abcdabcdabcd" contains "cdabcdab" as a substring.
```

**Example 2:**
```
Input: a = "a", b = "aa"
Output: 2
```

**Constraints:**
- `1 <= a.length, b.length <= 10^4`
- `a` and `b` consist of lowercase English letters.

---

## Observations

1. **Lower bound on repetitions:** To cover all `nb = len(b)` characters using blocks of length `na = len(a)`, we need at least `k = ceil(nb / na)` copies of `a`. With fewer copies, the repeated string is shorter than `b`, so it can never contain `b` as a substring.

2. **Why at most `k + 1` copies suffice (or it's impossible):** Any occurrence of `b` inside a repeated `a` can start at most `na - 1` characters into the first copy of `a` (an offset from 0 to `na - 1`). To cover `b` starting at the worst possible offset, we need the repeated string to have length at least `(na - 1) + nb`. This works out to at most `k + 1` repetitions. If `b` is not found in `a * (k + 1)`, it will never be found — the characters of `b` simply cannot be formed by repeating `a`.

3. **Impossibility:** If any character in `b` does not appear in `a`, it is immediately impossible. The algorithm handles this implicitly — `b in temp` will never be `True`.

4. **Why only two checks?** We only need to try `k` and `k + 1`. No further repetitions can help because any valid match must start within the first copy of `a` (offset `< na`), and adding more copies beyond `k + 1` does not expose any new starting positions that aren't already present.

---

## Solution

```python
import math

class Solution:
    def repeatedStringMatch(self, a: str, b: str) -> int:
        na, nb = len(a), len(b)

        # Minimum repetitions needed for the repeated string to be at least as long as b
        k = math.ceil(nb / na)

        def check(k: int) -> bool:
            return b in (a * k)

        # Check if b is a substring of a repeated k times
        if check(k):
            return k
        # b might start near the end of a copy and overflow into the next —
        # one extra copy is enough to cover that
        if check(k + 1):
            return k + 1
        # Characters in b cannot be formed by repeating a
        return -1
```

### Walkthrough — Example 1

- `a = "abcd"` (na = 4), `b = "cdabcdab"` (nb = 8)
- `k = ceil(8 / 4) = 2`
- `a * 2 = "abcdabcd"` — does not contain `"cdabcdab"` ✗
- `a * 3 = "abcdabcdabcd"` — contains `"cdabcdab"` ✓ → return **3**

### Walkthrough — Example 2

- `a = "a"` (na = 1), `b = "aa"` (nb = 2)
- `k = ceil(2 / 1) = 2`
- `a * 2 = "aa"` — contains `"aa"` ✓ → return **2**

### Complexity

| | Value |
|---|---|
| Time | O((na + nb) · nb) — substring search via Python's built-in (`in`) is O(na·k + nb) ≈ O(na + nb) amortized, but worst-case naive is O(n·m) |
| Space | O(na · k) for the temporary repeated string, which is O(na + nb) |
