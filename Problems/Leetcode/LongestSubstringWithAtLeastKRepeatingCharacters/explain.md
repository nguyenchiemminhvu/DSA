## Problem

https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/description/

Given a string `s` and an integer `k`, return the length of the **longest substring** of `s` such that the frequency of **each character** in this substring is greater than or equal to `k`. If no such substring exists, return `0`.

**Examples:**

- Input: `s = "aaabb"`, `k = 3` → Output: `3` (`"aaa"`)
- Input: `s = "ababbc"`, `k = 2` → Output: `5` (`"ababb"`)

---

## Observations

1. **Any character with count < k cannot appear in a valid substring.**  
   If a character appears fewer than `k` times across the entire string `s`, it can **never** satisfy the frequency requirement in any substring (since a substring can only have fewer or equal occurrences). Therefore, such a character acts as a **hard barrier** — no valid substring can cross it.

2. **Divide and conquer on barrier characters.**  
   Once we identify a "bad" character (count < k), we can safely **split** the string at every occurrence of that character. The answer must lie entirely within one of the resulting segments — never spanning across a split point.

3. **Base cases terminate the recursion cleanly.**  
   - If the string is empty, the answer is `0`.
   - If **every** character in `s` appears at least `k` times, then `s` itself is a valid substring, so the answer is `len(s)`.

4. **Each recursive call works on a strictly smaller substring.**  
   Since we split on a character that exists in `s`, each sub-problem is shorter than the original. This guarantees the recursion terminates.

5. **Complexity intuition.**  
   - There are at most 26 distinct lowercase letters, so the recursion depth is bounded by 26.
   - At each level, we scan the string to build a frequency counter: $O(n)$.
   - Overall time complexity is $O(n \cdot 26) = O(n)$ in practice, though a formal upper bound is $O(n \log n)$ or $O(n \cdot \text{unique chars})$.

---

## Solution Explanation

```python
from collections import Counter

class Solution:
    def longestSubstring(self, s: str, k: int) -> int:
        n = len(s)
        counter = Counter(s)           # (1) Count frequency of every character in s
        for ch in s:
            if counter[ch] < k:        # (2) Found a character that can never be in a valid window
                subs = s.split(ch)     # (3) Split s at every occurrence of that bad character
                res = 0
                for sub in subs:       # (4) Recurse on each segment independently
                    res = max(res, self.longestSubstring(sub, k))
                return res             # (5) Best answer among all segments
        return len(s)                  # (6) All characters satisfy freq >= k → entire s is valid
```

### Step-by-step walkthrough

| Step | What happens |
|------|-------------|
| **(1)** | Build a frequency map of all characters in the current substring `s`. |
| **(2)** | Iterate through `s` looking for the first character whose total count is below `k`. |
| **(3)** | That "bad" character is a guaranteed split point. Use `str.split(ch)` to break `s` into segments that don't contain `ch`. |
| **(4)** | Recursively solve each segment. Since `ch` is absent from every segment, the segments are independent sub-problems. |
| **(5)** | Return the maximum result across all segments — that's the longest valid substring in this call. |
| **(6)** | If the loop completes without finding any bad character, every character in `s` meets the threshold, so `s` itself is the answer. |

### Trace on Example 2: `s = "ababbc"`, `k = 2`

```
longestSubstring("ababbc", 2)
  counter = {a:2, b:3, c:1}
  'c' has count 1 < 2  →  split on 'c'  →  ["ababb", ""]
    longestSubstring("ababb", 2)
      counter = {a:2, b:3}   ← all counts >= 2
      return len("ababb") = 5          ✓
    longestSubstring("", 2)
      return 0
  return max(5, 0) = 5
```

### Why this is correct

The key insight is **correctness by elimination**: a character with count < k in `s` is provably absent from any valid substring. Splitting on it partitions the search space without losing any candidate solution. The recursion bottoms out when either the string is empty or all characters satisfy the constraint — both of which have trivially correct answers.

