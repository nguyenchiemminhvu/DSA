## Problem

https://leetcode.com/problems/find-the-sequence-of-strings-appeared-on-the-screen/description/

You are given a string `target`. Alice types `target` on a special keyboard that has only two keys:

- **Key 1**: Appends the character `"a"` to the current string on the screen.
- **Key 2**: Changes the **last character** of the current string to its next character in the English alphabet (`"a"` → `"b"`, ..., `"z"` → `"a"`).

Initially, the screen is empty (`""`), so Alice can only press Key 1 first.

Return a list of **all strings that appear on the screen** as Alice types `target`, **in order**, using the **minimum number of key presses**.

**Constraints:**
- `1 <= target.length <= 400`
- `target` consists only of lowercase English letters.

**Examples:**

Example 1: `target = "abc"`
- Press Key 1 → `"a"`
- Press Key 1 → `"aa"`
- Press Key 2 → `"ab"`
- Press Key 1 → `"aba"`
- Press Key 2 → `"abb"`
- Press Key 2 → `"abc"`
- **Output:** `["a","aa","ab","aba","abb","abc"]`

Example 2: `target = "he"`
- Press Key 1 seven times to reach `"h"` through `"a"` → `"b"` → ... → `"h"`.
- Press Key 1 → `"ha"`, then increment to `"he"`.
- **Output:** `["a","b","c","d","e","f","g","h","ha","hb","hc","hd","he"]`

## Observations

1. **Greedy character-by-character construction**: Each character of `target` is built independently. For each position `i`, we start from `'a'` (by appending with Key 1) and repeatedly press Key 2 until the character matches `target[i]`.

2. **Minimum presses per character**: To produce a character `c` at position `i`, the minimum presses required are:
   - 1 press of Key 1 (to append `'a'`).
   - `ord(target[i]) - ord('a')` presses of Key 2 (to increment from `'a'` to `target[i]`).
   - This is always optimal because Key 2 only moves forward in the alphabet and wrapping around (`'z'` → `'a'`) would be longer.

3. **All intermediate strings matter**: Every single key press produces a new string that must be recorded. We record the state after pressing Key 1 (which appends `'a'`) and after each press of Key 2 (which increments the last character).

4. **Simulation approach**: We maintain a current list of characters (`cur`) representing the string currently on screen. We process each target character by:
   - Recording the state after appending `'a'` (Key 1).
   - Incrementing the last character until it matches the target character, recording each intermediate state (Key 2).
   - Then appending `'a'` for the next position (via Key 1 in the next iteration).

5. **Order of operations**: After matching `cur[i]` to `target[i]`, we append `'a'` in preparation for the next character — this Key 1 press is recorded at the **start** of the next iteration.

## Solution

### Approach: Greedy Simulation

We simulate Alice's exact key presses character by character. At each position `i`:

1. **Append `'a'`** (Key 1): extend the current string by one character `'a'`. Record this state.
2. **Increment to target** (Key 2 repeatedly): while `cur[i] != target[i]`, increment `cur[i]` to the next alphabet character and record each intermediate state.

This guarantees minimum presses because:
- We always start fresh from `'a'` for each new character position.
- We move forward in the alphabet only (never backward), which is the shortest path from `'a'` to any target character.

```python
class Solution:
    def stringSequence(self, target: str) -> List[str]:
        res = []
        
        n = len(target)
        cur = ['a']
        i = 0
        while i < n:
            # Key 1 was pressed: record the state with 'a' appended at position i
            res.append(''.join(cur))
            
            # Press Key 2 until cur[i] matches target[i]
            while cur[i] != target[i]:
                cur[i] = chr(((ord(cur[i]) - ord('a') + 1) % 26) + ord('a'))
                res.append(''.join(cur))
            
            # Prepare for next character: append 'a' for position i+1
            cur.append('a')
            i += 1
        
        return res
```

**Step-by-step walkthrough for `target = "abc"`:**

| Step | Action | Screen |
|------|--------|--------|
| i=0: Key 1 pressed | Append `'a'` | `"a"` ✓ |
| i=0: `'a'` == `'a'` | Match! No Key 2 needed | — |
| i=1: Key 1 pressed | Append `'a'` | `"aa"` ✓ |
| i=1: `'a'` → `'b'` | Key 2 | `"ab"` ✓ |
| i=1: `'b'` == `'b'` | Match! | — |
| i=2: Key 1 pressed | Append `'a'` | `"aba"` ✓ |
| i=2: `'a'` → `'b'` | Key 2 | `"abb"` ✓ |
| i=2: `'b'` → `'c'` | Key 2 | `"abc"` ✓ |

**Output:** `["a", "aa", "ab", "aba", "abb", "abc"]`

**Time Complexity:** $O(n \times 26) = O(n)$ — For each of the `n` characters, we press Key 2 at most 25 times. Each string construction takes $O(n)$ time, so total is $O(n^2)$ in the worst case.

**Space Complexity:** $O(n)$ — The `cur` array holds the current string of length at most `n`.

# Tags
String | Simulation | Greedy
