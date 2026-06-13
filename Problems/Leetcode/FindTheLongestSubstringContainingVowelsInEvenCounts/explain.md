## Problem

https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/description/

Given a string `s`, return the length of the longest substring in which every vowel (`a`, `e`, `i`, `o`, `u`) appears an **even** number of times (including zero).

---

## Observations

1. **Even count = parity 0.** We only care whether each vowel count is even or odd, not the exact count. This collapses each vowel's count into a single bit: `0` = even, `1` = odd.

2. **State as a 5-tuple of parities.** At any position `i`, the "vowel parity state" is a 5-element tuple `(p_a, p_e, p_i, p_o, p_u)` where each `p_x` is the parity of how many times vowel `x` has appeared in `s[0..i]`. There are only $2^5 = 32$ distinct states.

3. **Same state means valid substring.** If the state at index `i` equals the state at index `j` (with `i < j`), then in the substring `s[i+1..j]` every vowel's count is even — because the parity changes cancel out. The longer the gap, the better.

4. **Store the first occurrence of each state.** To maximize the substring length, we want the earliest index at which each state was seen. We pre-insert state `(0,0,0,0,0)` at index `-1` to handle substrings starting from index `0`.

5. **No need to store the full count** — only the parity. This reduces the search space from $O(n^2)$ to $O(n)$.

---

## Solution Explanation

```python
class Solution:
    def findTheLongestSubstring(self, s: str) -> int:
        n = len(s)
        vowel = set('aeiou')
        vowel_to_idx = { c: i for i, c in enumerate('aeiou') }

        res = 0
        mp = {}
        masks = [0] * 5
        mp[tuple(masks)] = -1          # state (0,0,0,0,0) first seen before index 0
        for i, c in enumerate(s):
            if c in vowel:
                masks[vowel_to_idx[c]] = (masks[vowel_to_idx[c]] + 1) & 1  # flip parity

            state = tuple(masks)
            if state in mp:
                res = max(res, i - mp[state])  # substring s[mp[state]+1 .. i]
            else:
                mp[state] = i              # record first occurrence of this state

        return res
```

**Step-by-step walk-through:**

| Step | What happens |
|------|-------------|
| Initialize | `masks = [0,0,0,0,0]`, store state `(0,0,0,0,0)` → index `-1` |
| For each char `c` at index `i` | If `c` is a vowel, flip its bit in `masks` via `(val + 1) & 1` |
| Check state | If this state was seen before at index `j`, the substring `s[j+1..i]` has all-even vowel counts; update `res = max(res, i - j)` |
| New state | If never seen, record `mp[state] = i` (first occurrence only — earlier is always better for length) |

**Example trace** (`s = "leetc"`):

```
i=0 'l': state=(0,0,0,0,0) → seen at -1 → res=max(0, 0-(-1))=1
i=1 'e': flip e → state=(0,1,0,0,0) → new → mp[(0,1,0,0,0)]=1
i=2 'e': flip e → state=(0,0,0,0,0) → seen at -1 → res=max(1, 2-(-1))=3
i=3 't': state=(0,0,0,0,0) → seen at -1 → res=max(3, 3-(-1))=4
i=4 'c': state=(0,0,0,0,0) → seen at -1 → res=max(4, 4-(-1))=5
```
Result: `5` ✓

---

## Complexity

| | |
|---|---|
| **Time** | $O(n)$ — single pass; state lookup/insert is $O(1)$ (at most 32 states) |
| **Space** | $O(1)$ — the hashmap holds at most $2^5 = 32$ entries |
