## Problem

https://leetcode.com/problems/string-to-integer-atoi/description/

Implement the `myAtoi(string s)` function, which converts a string to a 32-bit signed integer.

The algorithm follows these steps in order:

1. **Whitespace**: Ignore any leading whitespace characters (`' '`).
2. **Signedness**: Determine the sign by checking if the next character is `'-'` or `'+'`. Assume positive if neither is present.
3. **Conversion**: Read digits, skipping leading zeros, until a non-digit character is encountered or the string ends. If no digits are read, return `0`.
4. **Rounding**: Clamp the result to the 32-bit signed integer range $[-2^{31},\ 2^{31}-1]$.

**Constraints:**
- `0 <= s.length <= 200`
- `s` consists of English letters, digits (`0-9`), `' '`, `'+'`, `'-'`, and `'.'`.

---

## Observations

- The problem is essentially a **simulation/parsing** problem — carefully follow the specified steps in exact order.
- The four steps form a strict pipeline: strip whitespace → read sign → read digits → clamp.
- **Only leading whitespace** is stripped. Whitespace appearing after the sign or digits stops parsing entirely.
- A sign character (`+` or `-`) is consumed only if it is the **very first non-whitespace character**. A sign appearing after any digit (e.g. `"0-1"`) is treated as a non-digit stop character.
- Digit reading stops immediately at the **first non-digit** character; everything after is ignored.
- **Overflow must be detected before it happens**, not after. Once `result` is multiplied by 10 and a digit is added, it may already exceed a 64-bit integer in some languages. The safe check is:
  - If `result > INT_MAX // 10`, the next multiplication will overflow → clamp immediately.
  - If `result == INT_MAX // 10` and the incoming digit `> INT_MAX % 10` (i.e., `> 7`), adding it will overflow → clamp immediately.
- The clamp value depends on the **sign** determined in step 2:
  - overflow with positive sign → return `INT_MAX` ($2^{31}-1 = 2147483647$)
  - overflow with negative sign → return `INT_MIN` ($-2^{31} = -2147483648$)
- Python integers are arbitrary precision, so the overflow check here is purely logical (to match the 32-bit contract), not a language necessity.

---

## Solution

```python
class Solution:
    def myAtoi(self, s: str) -> int:
        # Step 1 — strip leading whitespace
        s = s.lstrip()
        if not s:
            return 0

        sign = 1
        i = 0
        n = len(s)

        # Step 2 — read optional sign character
        if s[i] == '+' or s[i] == '-':
            if s[i] == '-':
                sign = -1
            i += 1

        INT_MAX = 2**31 - 1   # 2147483647
        INT_MIN = -2**31      # -2147483648

        # Step 3 & 4 — read digits and clamp on overflow
        result = 0
        while i < n and s[i].isdigit():
            digit = ord(s[i]) - ord('0')

            # Check overflow BEFORE updating result
            if result > INT_MAX // 10 or (result == INT_MAX // 10 and digit > INT_MAX % 10):
                return INT_MAX if sign == 1 else INT_MIN

            result = result * 10 + digit
            i += 1

        return sign * result
```

### Step-by-step walkthrough

| Step | Action | Detail |
|------|--------|--------|
| 1 | `s.lstrip()` | Removes all leading spaces in one call. If the result is empty, return `0` immediately. |
| 2 | Sign detection | Check `s[0]` (after stripping). Set `sign = -1` for `'-'`, keep `sign = 1` otherwise. Advance index `i` past the sign character. |
| 3 | Digit loop | `s[i].isdigit()` naturally handles leading zeros — they just contribute `0` to `result`. The loop exits the moment a non-digit is seen. |
| 4 | Overflow guard | Before `result = result * 10 + digit`, check if that operation would exceed `INT_MAX`. The two conditions cover: (a) the current `result` is already too large to multiply by 10, (b) multiplying by 10 is fine but adding the new digit tips it over. Return the appropriate clamp value multiplied by `sign`. |
| 5 | Return | `sign * result` applies the sign in a single multiplication. |

### Complexity

| | |
|-|---|
| **Time** | $O(n)$ — single pass through the string |
| **Space** | $O(1)$ — only a handful of scalar variables |
