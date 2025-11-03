## Problem

https://leetcode.com/problems/rotate-string/description/

```
Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.

A shift on s consists of moving the leftmost character of s to the rightmost position.

For example, if s = "abcde", then it will be "bcdea" after one shift.

Example 1:

Input: s = "abcde", goal = "cdeab"
Output: true

Example 2:

Input: s = "abcde", goal = "abced"
Output: false

Constraints:

1 <= s.length, goal.length <= 100
s and goal consist of lowercase English letters.
```

## Observations

1. **String Length Constraint**: If `s` and `goal` have different lengths, it's impossible for one to be a rotation of the other, so we can return `False` immediately.

2. **Rotation Definition**: A rotation means moving characters from the beginning to the end. For example:
   - `"abcde"` → `"bcdea"` (moved 'a' to the end)
   - `"abcde"` → `"cdeab"` (moved 'ab' to the end)

3. **All Possible Rotations**: For a string of length `n`, there are exactly `n` possible rotations (including the original string). We need to check if any of these rotations matches `s`.

4. **Key Insight**: Instead of rotating `s` to match `goal`, we can rotate `goal` to match `s`. This is what the solution does - it tries all possible rotations of `goal`.

5. **String Slicing Approach**: `goal[i:] + goal[0:i]` creates a rotation of `goal` where we take everything from index `i` to the end, followed by everything from the beginning to index `i-1`.

## Solution

1. **Length Check**: First, verify that both strings have the same length. If not, return `False`.

2. **Try All Rotations**: For each position `i` from 0 to `n-1`:
   - Create a rotation of `goal` by concatenating `goal[i:]` + `goal[0:i]`
   - This effectively "rotates" the string by moving the first `i` characters to the end
   - Check if this rotation equals `s`

3. **Early Return**: If any rotation matches `s`, return `True`. If no rotation matches after trying all possibilities, return `False`.

**Example Walkthrough:**
- `s = "abcde"`, `goal = "cdeab"`
- `i = 0`: `"cdeab"[0:] + "cdeab"[0:0]` = `"cdeab"` ≠ `"abcde"`
- `i = 1`: `"cdeab"[1:] + "cdeab"[0:1]` = `"deab"` + `"c"` = `"deabc"` ≠ `"abcde"`
- `i = 2`: `"cdeab"[2:] + "cdeab"[0:2]` = `"eab"` + `"cd"` = `"eabcd"` ≠ `"abcde"`
- `i = 3`: `"cdeab"[3:] + "cdeab"[0:3]` = `"ab"` + `"cde"` = `"abcde"` = `"abcde"` ✓

**Time Complexity:** O(n²) - We check n rotations, and each string comparison takes O(n) time.
**Space Complexity:** O(n) - For creating the rotated strings during comparison.

**Alternative Elegant Solution:**
A more elegant approach uses the fact that if `goal` is a rotation of `s`, then `goal` will appear as a substring in `s + s`:
```python
def rotateString(self, s: str, goal: str) -> bool:
    return len(s) == len(goal) and goal in s + s
```
This works because `s + s` contains all possible rotations of `s` as substrings.

# Tags

- String Manipulation
- String Rotation
- Brute Force
- Array/String

