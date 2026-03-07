## Problem

https://leetcode.com/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/description/

```
You are given a binary string s. You are allowed to perform two types of operations on the string in any sequence:

Type-1: Remove the character at the start of the string s and append it to the end of the string.
Type-2: Pick any character in s and flip its value, i.e., if its value is '0' it becomes '1' and vice-versa.

Return the minimum number of type-2 operations you need to perform such that s becomes alternating.

The string is called alternating if no two adjacent characters are equal.
For example, the strings "010" and "1010" are alternating, while the string "0100" is not.

Example 1:
Input: s = "111000"
Output: 2
Explanation: Use the first operation two times to make s = "100011".
Then, use the second operation on the third and sixth elements to make s = "101010".

Example 2:
Input: s = "010"
Output: 0
Explanation: The string is already alternating.

Example 3:
Input: s = "1110"
Output: 1
Explanation: Use the second operation on the second element to make s = "1010".

Constraints:
1 <= s.length <= 105
s[i] is either '0' or '1'.
```

## Observations

1. **Only two target patterns exist**: For any length `n`, there are exactly two alternating strings:
   - `pattern1 = "010101..."` (starts with `'0'`, even indices are `'0'`)
   - `pattern2 = "101010..."` (starts with `'1'`, even indices are `'1'`)
   The two patterns are bitwise complements of each other, so for any position `i`, `pattern1[i] != pattern2[i]`.

2. **Type-1 is a free rotation**: A Type-1 operation removes the first character and appends it to the end — this is simply a left rotation of the string. Applying it `k` times gives the rotation `s[k:] + s[:k]`. Since it costs nothing, we want to find the rotation that requires the fewest Type-2 flips.

3. **All rotations live inside `s + s`**: The rotation by `k` positions is the substring `(s+s)[k : k+n]`. By doubling the string, we can check every possible rotation as a sliding window of size `n` over `s+s` (positions `k = 0, 1, ..., n-1`).

4. **Complementary cost property**: Because the two patterns are complements, for every position `i` a character `s[i]` matches exactly one of them. Therefore `diff1 + diff2 = n` always holds for any window of size `n`. This means `min(diff1, diff2) <= n // 2` — we never need more than half the window flipped.

5. **Sliding window is O(n)**: When we slide the window one step to the right:
   - **Add** the incoming right character: increment `diff1` or `diff2` if it mismatches its pattern position.
   - **Remove** the outgoing left character: decrement `diff1` or `diff2` if it had mismatched its pattern position.
   This lets us update both counts in O(1) per step.

## Solution

The solution combines **string doubling** with a **fixed-size sliding window** of length `n`.

### Algorithm Steps

1. **Double the string**: set `s = s + s` (length `2n`). Build `pattern1` and `pattern2` of the same length `2n`.
2. **Bootstrap the first window** `[0, n-1]`: count `diff1` (mismatches vs `pattern1`) and `diff2` (mismatches vs `pattern2`).
3. **Initialize result**: `res = min(diff1, diff2)`.
4. **Slide the window** from `right = n` to `right = 2n-1`:
   - Expand right: update `diff1`/`diff2` for the new character at `right`.
   - Shrink left: update `diff1`/`diff2` by removing the character at `left`, then advance `left`.
   - Update `res = min(res, min(diff1, diff2))`.
5. Return `res`.

### Walkthrough — Example 1: `s = "111000"`

```
n = 6
s doubled = "111000111000"
pattern1  = "010101010101"
pattern2  = "101010101010"

Initial window [0,5] = "111000":
  diff1 (vs "010101") = positions 0,1,3,4 differ → 4
  diff2 (vs "101010") = positions 2,5 differ       → 2
  res = min(4, 2) = 2

Slide right=6, left=0 (window = "110001"):
  add s[6]='1': matches pattern1[6]='0'? No → diff1=5; matches pattern2[6]='1'? Yes → diff2 unchanged
  remove s[0]='1': mismatched pattern1[0]='0' → diff1=4; matched pattern2[0]='1' → diff2 unchanged
  res = min(2, min(4,2)) = 2

... (subsequent windows also yield ≥ 2)

Final answer: 2 ✓
```

### Complexity

| |  |
|---|---|
| **Time** | O(n) — one pass to build patterns, one pass for the sliding window |
| **Space** | O(n) — for the doubled string and the two patterns |

### Code

```python
class Solution:
    def minFlips(self, s: str) -> int:
        n = len(s)
        s += s
        new_n = len(s)

        pattern1 = ''
        pattern2 = ''
        for i in range(new_n):
            pattern1 += '1' if i & 1 else '0'
            pattern2 += '0' if i & 1 else '1'

        diff1 = 0
        diff2 = 0
        for i in range(n):
            if s[i] != pattern1[i]:
                diff1 += 1
            if s[i] != pattern2[i]:
                diff2 += 1

        res = min(diff1, diff2)
        left = 0
        for right in range(n, new_n):
            if s[right] != pattern1[right]:
                diff1 += 1
            if s[right] != pattern2[right]:
                diff2 += 1

            if s[left] != pattern1[left]:
                diff1 -= 1
            if s[left] != pattern2[left]:
                diff2 -= 1
            left += 1

            res = min(res, min(diff1, diff2))
        return res
```

# Tags

`sliding-window` `string` `greedy`

