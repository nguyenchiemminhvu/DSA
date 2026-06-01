## Problem

https://leetcode.com/problems/find-and-replace-pattern/description/

Given a list of strings `words` and a string `pattern`, return a list of `words[i]` that match the pattern. You may return the answer in any order.

A word matches the pattern if there exists a **permutation of letters** `p` such that after replacing every letter `x` in the pattern with `p(x)`, we get the desired word.

A permutation of letters is a **bijection** from letters to letters: every letter maps to another letter, and no two letters map to the same letter.

**Example:**
```
Input:  words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
Output: ["mee","aqq"]

"mee" matches: {a->m, b->e} — valid bijection
"ccc" does not match: {a->c, b->c} — not a bijection (a and b both map to c)
```

---

## Observations

1. **Same length requirement.** A word can only match the pattern if it has the same length, which the constraints guarantee.

2. **The problem reduces to isomorphism.** Two strings are *isomorphic* if they have the same structural pattern of repeated characters. For example, `"abb"` and `"mee"` are isomorphic because both follow the pattern `[x, y, y]`. Matching a word against the pattern is exactly checking whether the word and the pattern are isomorphic.

3. **Bijection requires two-way mapping.** A single forward map (`pattern char → word char`) is not enough. Consider `pattern = "ab"`, `word = "aa"`: `a→a` and `b→a` would satisfy the forward direction, but `b` and `a` both map to the same letter, violating the bijection. We need a reverse map (`word char → pattern char`) as well to enforce that the mapping is one-to-one in both directions.

4. **Time complexity:** `O(N * L)` where `N` is the number of words and `L` is the pattern length — we scan each character of each word once.

---

## Solution

The core helper `is_isomorphic(s, t)` checks whether word `s` and pattern `t` are isomorphic using two dictionaries:

- `ds`: maps a character in `s` → its paired character in `t`
- `dt`: maps a character in `t` → its paired character in `s`

At each position `i`:
- If `s[i]` was already mapped, it **must** map to `t[i]` (consistency check).
- If `t[i]` was already mapped, it **must** map back to `s[i]` (bijection check).
- Otherwise, record the new pairing in both dictionaries.

If all positions pass without conflict, the two strings are isomorphic and the word matches the pattern.

```python
class Solution:
    def findAndReplacePattern(self, words: List[str], pattern: str) -> List[str]:
        def is_isomorphic(s: str, t: str) -> bool:
            ns, nt = len(s), len(t)
            if ns != nt:
                return False

            ds, dt = {}, {}
            for i in range(ns):
                cs, ct = s[i], t[i]
                if cs in ds and ds[cs] != ct:   # forward mapping conflict
                    return False
                if ct in dt and dt[ct] != cs:   # reverse mapping conflict (bijection)
                    return False
                ds[cs] = ct
                dt[ct] = cs

            return True

        res = []
        for word in words:
            if is_isomorphic(word, pattern):
                res.append(word)
        return res
```

**Walkthrough for `words = ["mee", "ccc"]`, `pattern = "abb"`:**

| i | cs  | ct  | ds after       | dt after       | conflict? |
|---|-----|-----|----------------|----------------|-----------|
| **"mee"** |
| 0 | `m` | `a` | `{m:a}`        | `{a:m}`        | No        |
| 1 | `e` | `b` | `{m:a, e:b}`   | `{a:m, b:e}`   | No        |
| 2 | `e` | `b` | `{m:a, e:b}`   | `{a:m, b:e}`   | No (consistent) |
| → match ✓ |
| **"ccc"** |
| 0 | `c` | `a` | `{c:a}`        | `{a:c}`        | No        |
| 1 | `c` | `b` | `ds[c]=a ≠ b`  | —              | **Yes** → return False |
| → no match ✗ |
