## Problem

https://leetcode.com/problems/vowels-game-in-a-string/description/

Alice and Bob take turns removing substrings from string `s` (Alice goes first). Alice must remove a substring with an **odd** number of vowels; Bob must remove a substring with an **even** number of vowels. The first player who cannot make a valid move **loses**. Return `true` if Alice wins (both play optimally).

---

## Observations

1. **Alice's only constraint** is that she must find at least one substring containing an odd number of vowels. The smallest such substring is a single vowel character. So Alice **can move if and only if there is at least one vowel** in `s`.

2. **If total vowels = 0:** Alice has no valid move on her very first turn → Alice loses immediately.

3. **If total vowels > 0:** Alice always wins, regardless of parity. Here's why:

   - **Case A — total vowels is odd:**  
     Alice removes the **entire string** in one move (odd vowels). Bob faces an empty string with no valid move → Bob loses.

   - **Case B — total vowels is even (and > 0):**  
     Alice removes a **single vowel** (a length-1 substring = 1 vowel, which is odd).  
     Now `count - 1` vowels remain, which is **odd**.  
     Bob must remove a substring with an **even** number of vowels:
     - If Bob removes **0 vowels** (consonants only): odd vowels still remain for Alice.
     - If Bob removes **k vowels (k even, k > 0)**: `odd - even = odd` vowels remain for Alice.
     
     In both sub-cases, Alice always faces a positive **odd** count of vowels, so she can always grab the entire remaining string (odd vowels) and leave Bob with nothing.  
     Bob is eventually forced into a position with 0 vowels and 0 is even, but there must be a **non-empty** substring to remove — if nothing is left, Bob cannot move → Bob loses.

4. **Summary:** The entire game reduces to one single question — *does `s` contain at least one vowel?*

---

## Solution

```python
class Solution:
    def doesAliceWin(self, s: str) -> bool:
        count = 0
        vowel = set('aeiou')
        for c in s:
            if c in vowel:
                count += 1
        
        if count > 0:
            return True
        return False
```

**Simplified one-liner:**
```python
class Solution:
    def doesAliceWin(self, s: str) -> bool:
        return any(c in 'aeiou' for c in s)
```

**Complexity:**
- Time: $O(n)$ — single pass through the string.
- Space: $O(1)$ — only a counter is stored.
