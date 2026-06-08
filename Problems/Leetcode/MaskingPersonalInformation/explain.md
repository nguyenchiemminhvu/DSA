## Problem

https://leetcode.com/problems/masking-personal-information/description

Given a personal information string `s` — either an email or a phone number — return its masked form.

**Email masking rules:**
- Lowercase the entire string.
- Replace the middle of the name (everything between the first and last character before `@`) with exactly 5 asterisks `*****`.
- Result form: `a*****b@domain.tld`

**Phone masking rules:**
- Strip all separation characters (`+`, `-`, `(`, `)`, space).
- Keep only digits. The last 10 digits are the local number; any extra digits (0–3) are the country code.
- Result forms:
  - 0 extra digits: `***-***-XXXX`
  - 1 extra digit:  `+*-***-***-XXXX`
  - 2 extra digits: `+**-***-***-XXXX`
  - 3 extra digits: `+***-***-***-XXXX`
- `XXXX` is the last 4 digits.

---

## Observations

1. **Dispatch on `@`**: the presence of `@` is the only reliable way to distinguish an email from a phone number (phone numbers never contain `@`).

2. **Email — only the name's middle changes**: the domain is lowercased but otherwise untouched. The name keeps its first and last character; everything in between is replaced by a fixed 5-asterisk string regardless of how long the name is.

3. **Phone — digits are all that matter**: the separation characters are noise; once stripped, the total digit count drives the format. The last 4 digits appear in plaintext; the rest are masked with `*`.

4. **Country code length = `total_digits − 10`**: since the local number is always exactly 10 digits, any excess directly gives the country code length.

---

## Solution walkthrough

```python
class Solution:
    def maskPII(self, s: str) -> str:
        def mask_email(s: str):
            letters = []
            pivot = -1
            for i, c in enumerate(s):
                if c == '@' and pivot == -1:
                    pivot = i          # record position of '@'
                letters.append(c.lower())
            # letters[:1]       → first char of name
            # list('*****')     → fixed 5-asterisk middle
            # letters[pivot-1:] → last char of name + '@' + full domain
            return ''.join(letters[:1] + list('*****') + letters[pivot - 1:])

        def mask_phone(s: str):
            digits = [c for c in s if c.isdigit()]
            n = len(digits)
            country_len = n - 10          # 0, 1, 2, or 3
            if country_len > 0:
                prefix = '+' + '*' * country_len + '-'
            else:
                prefix = ''
            return prefix + '***-***-' + ''.join(digits[-4:])

        if '@' in s:
            return mask_email(s)
        else:
            return mask_phone(s)
```

**`mask_email` step by step**

| Step | What happens |
|------|--------------|
| Iterate with index | Lowercase every character; record `pivot` (index of `@`) on first encounter. |
| Slice `letters[:1]` | First character of the name. |
| `list('*****')` | Always exactly 5 asterisks. |
| Slice `letters[pivot-1:]` | Starts at the last character of the name, then continues with `@` and the full domain. |

Because `pivot` is the index of `@`, `pivot - 1` is the index of the last name character. This works even when the name is only 2 characters long (e.g., `"AB@qq.com"` → `"a*****b@qq.com"`).

**`mask_phone` step by step**

| Step | What happens |
|------|--------------|
| Filter digits | All non-digit characters are discarded. |
| `country_len = n - 10` | 10–13 digits total; subtracting 10 gives 0–3. |
| Build prefix | Empty string for 0 country digits; `+*…-` with the right number of `*` otherwise. |
| Append fixed mask + last 4 | `***-***-` is always present; `digits[-4:]` gives the visible local suffix. |

**Complexity**

- Time: O(n) — single pass through the string for each helper.
- Space: O(n) — for the collected characters/digits list.
