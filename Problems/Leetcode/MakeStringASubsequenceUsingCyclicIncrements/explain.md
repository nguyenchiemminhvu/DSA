## Problem

https://leetcode.com/problems/make-string-a-subsequence-using-cyclic-increments/description/

Given two 0-indexed strings `str1` and `str2`, you may select any set of indices in `str1` and increment each chosen character cyclically (`'a'`→`'b'`, …, `'z'`→`'a'`) — all at once, in a single operation. Return `true` if `str2` can be made a subsequence of `str1` using **at most one** such operation.

---

## Observations

- Because all increments happen simultaneously in one operation, each character in `str1` can be used in at most two states: its original character, or its cyclic successor.
- A character `str1[i]` can match `str2[j]` if:
  - `str1[i] == str2[j]` (no increment needed), or
  - `(str1[i] - 'a' + 1) % 26 + 'a' == str2[j]` (increment by one cyclically).
- The problem therefore reduces to: can we find a subsequence match where each `str1` character is matched against either itself or its next character?
- The "at most once" operation constraint does **not** restrict which indices we pick — it only means we cannot increment a character by 2 or more. Every index can independently be incremented or not, so there is no global state to track across characters.

---

## Solution Explanation

Use a standard two-pointer subsequence check, but relax the equality condition to also accept a cyclic +1 match.

```python
class Solution:
    def canMakeSubsequence(self, a: str, b: str) -> bool:
        ia, ib = 0, 0
        na, nb = len(a), len(b)
        
        while ia < na and ib < nb:
            if a[ia] == b[ib] or chr((ord(a[ia]) - ord('a') + 1) % 26 + ord('a')) == b[ib]:
                ib += 1
            
            ia += 1
        
        return ib == nb
```

- `ia` walks through `str1`; `ib` walks through `str2`.
- For each `a[ia]`, compute its cyclic successor with `(ord(a[ia]) - ord('a') + 1) % 26 + ord('a')`. The `% 26` wraps `'z'` back to `'a'`.
- If either the original or the successor matches `b[ib]`, advance `ib` (the character in `str2` is "consumed").
- Always advance `ia` regardless.
- After the loop, `ib == nb` means every character of `str2` was matched in order — i.e., `str2` is achievable as a subsequence.

**Time:** O(n + m) — single pass through both strings.  
**Space:** O(1) — no auxiliary data structures.
