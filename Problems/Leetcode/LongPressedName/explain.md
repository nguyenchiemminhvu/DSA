## Problem

https://leetcode.com/problems/long-pressed-name/description/

```
Your friend is typing his name into a keyboard. Sometimes, when typing a character c, the key might get long pressed, and the character will be typed 1 or more times.

You examine the typed characters of the keyboard. Return True if it is possible that it was your friends name, with some characters (possibly none) being long pressed.

Example 1:

Input: name = "alex", typed = "aaleex"
Output: true
Explanation: 'a' and 'e' in 'alex' were long pressed.

Example 2:

Input: name = "saeed", typed = "ssaaedd"
Output: false
Explanation: 'e' must have been pressed twice, but it was not in the typed output.

Constraints:

1 <= name.length, typed.length <= 1000
name and typed consist of only lowercase English letters.
```

## Observations

1. **Two-pointer approach**: We need to compare characters from both strings `s` (name) and `t` (typed), advancing pointers based on matching conditions.

2. **Character matching**: When characters match between `s[idx_s]` and `t[idx_t]`, we advance both pointers and remember the current character as `prev`.

3. **Long press handling**: When characters don't match, we check if the current character in `t` is the same as the previously matched character (`prev`). If yes, it's a valid long press; if no, it's invalid.

4. **Edge cases**:
   - After processing all characters in `s`, there might be remaining characters in `t` that should all be repetitions of the last matched character
   - Both strings must be fully consumed for a valid match

5. **Key insight**: The `prev` variable tracks the last successfully matched character, allowing us to validate if extra characters in `t` are legitimate long presses.

## Solution

The solution uses a **two-pointer technique** with character tracking:

### Algorithm Steps:

1. **Initialize pointers and variables**:
   - `idx_s`, `idx_t`: pointers for strings `s` and `t`
   - `prev`: tracks the last matched character (initialized to '#' as sentinel)

2. **Main matching loop**:
   ```python
   while idx_s < ns and idx_t < nt:
       if s[idx_s] == t[idx_t]:  # Characters match
           prev = s[idx_s]       # Update last matched character
           idx_s += 1            # Advance both pointers
           idx_t += 1
       else:                     # Characters don't match
           if t[idx_t] != prev:  # Not a valid long press
               return False
           idx_t += 1            # Skip the long-pressed character
   ```

3. **Handle remaining characters in `t`**:
   ```python
   while idx_t < nt:
       if t[idx_t] != prev:     # Extra character not from long press
           return False
       idx_t += 1
   ```

4. **Final validation**: Both strings must be fully processed (`idx_s == ns and idx_t == nt`)

### Example Walkthrough:

**Input**: `s = "alex"`, `t = "aaleex"`

| Step | idx_s | idx_t | s[idx_s] | t[idx_t] | prev | Action |
|------|-------|-------|----------|----------|------|---------|
| 1    | 0     | 0     | 'a'      | 'a'      | '#'  | Match: prev='a', advance both |
| 2    | 1     | 1     | 'l'      | 'a'      | 'a'  | No match, but t[1]=='a'==prev, advance t |
| 3    | 1     | 2     | 'l'      | 'l'      | 'a'  | Match: prev='l', advance both |
| 4    | 2     | 3     | 'e'      | 'e'      | 'l'  | Match: prev='e', advance both |
| 5    | 3     | 4     | 'x'      | 'e'      | 'e'  | No match, but t[4]=='e'==prev, advance t |
| 6    | 3     | 5     | 'x'      | 'x'      | 'e'  | Match: prev='x', advance both |
| 7    | 4     | 6     | -        | -        | 'x'  | Both strings consumed → True |

### Time Complexity: O(n + m) where n = len(s), m = len(t)
### Space Complexity: O(1) - only using constant extra space

# Tags

Two Pointers, String Matching, Character Validation

