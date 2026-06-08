## Problem

https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/description/

Given a 0-indexed binary string `s` of **even length**, return the **minimum number of character changes** to make `s` **beautiful**.

A string is **beautiful** if it can be partitioned into one or more substrings where:
- Each substring has **even length**.
- Each substring contains **only `'1'`s or only `'0'`s**.

---

## Key Insight

Because every partition piece must have **even length** and be **homogeneous**, the smallest valid unit is a pair of identical characters: `"00"` or `"11"`.

We can always tile the entire string with non-overlapping pairs at fixed positions:

```
index:  0  1 | 2  3 | 4  5 | ...
pair:  (0,1) | (2,3) | (4,5) | ...
```

Each pair must satisfy `s[i] == s[i+1]`. If a pair is mismatched (e.g. `"01"` or `"10"`), we need **exactly 1 change** to fix it (change either character to match the other).

> **Why can we always fix each pair independently?**  
> Because fixing one pair never affects an adjacent pair — the boundaries are fixed at even indices.

---

## Solution Walkthrough

```python
class Solution:
    def minChanges(self, s: str) -> int:
        n = len(s)

        res = 0
        for i in range(1, n, 2):   # visit the right element of each pair: indices 1, 3, 5, ...
            if s[i] != s[i - 1]:   # pair (i-1, i) is mismatched
                res += 1           # one change is enough to unify the pair
        return res
```

**Step-by-step:**

| Iteration | Pair checked | Mismatched? | `res` |
|-----------|-------------|-------------|-------|
| `i = 1`   | `(s[0], s[1])` | if yes → +1 | ... |
| `i = 3`   | `(s[2], s[3])` | if yes → +1 | ... |
| `i = 5`   | `(s[4], s[5])` | if yes → +1 | ... |
| ...       | ...            | ...         | ... |

---

## Trace Through Examples

**Example 1:** `s = "1001"`

| Pair | Characters | Mismatched? |
|------|-----------|-------------|
| (0,1) | `'1','0'` | ✅ yes → +1 |
| (2,3) | `'0','1'` | ✅ yes → +1 |

Result: `2` ✔

**Example 2:** `s = "10"`

| Pair | Characters | Mismatched? |
|------|-----------|-------------|
| (0,1) | `'1','0'` | ✅ yes → +1 |

Result: `1` ✔

**Example 3:** `s = "0000"`

| Pair | Characters | Mismatched? |
|------|-----------|-------------|
| (0,1) | `'0','0'` | ❌ no |
| (2,3) | `'0','0'` | ❌ no |

Result: `0` ✔

---

## Complexity

| | |
|---|---|
| **Time** | $O(n)$ — one pass through the string |
| **Space** | $O(1)$ — only a counter variable |
