## Problem

https://leetcode.com/problems/trim-trailing-vowels/description/

Given a string `s` consisting of lowercase English letters, return the string obtained by removing all **trailing vowels** from `s`.

Vowels are: `'a'`, `'e'`, `'i'`, `'o'`, `'u'`.

**Examples:**
- `"idea"` → `"id"` (trailing `"ea"` removed)
- `"day"` → `"day"` (no trailing vowels)
- `"aeiou"` → `""` (entire string is vowels)

**Constraints:**
- `1 <= s.length <= 100`
- `s` consists of only lowercase English letters.

## Observations

- "Trailing" means we only care about the **end** of the string, not the middle or beginning.
- We stop removing as soon as we hit a consonant (or the string becomes empty).
- The problem is purely about scanning from the right until a non-vowel character is found.
- Since `s.length <= 100`, even an O(n) repeated slicing approach is perfectly fine within constraints.
- Edge cases:
  - All vowels → return empty string `""`.
  - No trailing vowels → return `s` unchanged.
  - Single character: if vowel → `""`, if consonant → same character.

## Solution

**Approach: Shrink from the right**

Repeatedly check the last character of the string. If it is a vowel, remove it. Continue until the string is empty or the last character is a consonant.

```python
class Solution:
    def trimTrailingVowels(self, s: str) -> str:
        while len(s) and s[-1] in "aeiou":
            s = s[:-1]
        return s
```

**Step-by-step walkthrough (`s = "idea"`):**

| Iteration | `s`      | `s[-1]` | Is vowel? |
|-----------|----------|---------|-----------|
| 1         | `"idea"` | `'a'`   | Yes → remove |
| 2         | `"ide"`  | `'e'`   | Yes → remove |
| 3         | `"id"`   | `'d'`   | No → stop |

**Result:** `"id"` ✓

**Complexity:**
- Time: O(n) — at most `n` characters are removed one by one.
- Space: O(n) — each `s[:-1]` creates a new string (Python strings are immutable). Can be made O(1) extra space by finding the cutoff index and slicing once:

```python
class Solution:
    def trimTrailingVowels(self, s: str) -> str:
        i = len(s) - 1
        while i >= 0 and s[i] in "aeiou":
            i -= 1
        return s[:i + 1]
```

This variant scans right-to-left with a pointer and performs a **single slice** at the end, which is slightly more efficient in practice.

# Tags

`String` `Two Pointers`
