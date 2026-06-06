## Problem

https://leetcode.com/problems/valid-number/description/

Given a string `s`, return whether `s` is a **valid number**.

A valid number is either:
- An **integer** (optional sign + digits), optionally followed by an **exponent** (`e`/`E` + integer).
- A **decimal** (optional sign + digits/dot combinations), optionally followed by an **exponent**.

Valid examples: `"2"`, `"-0.1"`, `"+3.14"`, `"4."`, `"-.9"`, `"2e10"`, `"3e+7"`, `"53.5e93"`  
Invalid examples: `"abc"`, `"1a"`, `"1e"`, `"e3"`, `"99e2.5"`, `"--6"`, `"-+3"`

---

## Observations

1. **The grammar is exactly what `float()` parses** — Python's built-in `float()` accepts the same set of strings the problem defines as valid: optional sign, integer/decimal bodies, and `e`/`E` exponents with optional sign.

2. **Python's `float()` accepts a few extra strings** that are *not* valid per this problem:
   - `"inf"`, `"infinity"`, `"nan"` — these are accepted by `float()` but contain no digits.
   - The digit-presence guard `all(c not in s for c in '1234567890')` rejects them by requiring at least one digit character.

3. **Edge cases naturally rejected by `float()`**: `"1e"` (exponent with no value), `"99e2.5"` (decimal exponent), `"--6"` (double sign), `"e3"` (no mantissa), `"."` (dot alone) — all raise `ValueError`.

4. **Constraint guarantee**: the input only contains `[A-Za-z0-9+\-.]`, so Python-specific oddities like underscores in numeric literals (`"1_000"`) or leading/trailing whitespace never appear.

---

## Solution

```python
class Solution:
    def isNumber(self, s: str) -> bool:
        try:
            if all(c not in s for c in '1234567890'):
                return False
            float(s)
        except:
            return False
        return True
```

### How it works

| Step | Code | Purpose |
|------|------|---------|
| 1 | `all(c not in s for c in '1234567890')` | Reject digit-free strings (`"inf"`, `"nan"`, `"e"`, `"."`) that `float()` would accept or that should be invalid. |
| 2 | `float(s)` inside `try/except` | Delegates all grammar validation to Python's parser. Raises `ValueError` for anything malformed. |
| 3 | Return `True` | If both checks pass, the string is a valid number. |

### Complexity

- **Time**: O(n) — `float()` scans the string once.
- **Space**: O(1) — no extra data structures.
