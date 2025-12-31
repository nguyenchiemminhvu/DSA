# Check If A Parentheses String Can Be Valid

## Problem

https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/description/

A parentheses string is a **non-empty** string consisting only of `'('` and `')'`. It is valid if any of the following conditions is true:

1. It is `"()"`
2. It can be written as `AB` (A concatenated with B), where A and B are valid parentheses strings
3. It can be written as `(A)`, where A is a valid parentheses string

You are given:
- A parentheses string `s` of length `n`
- A string `locked` of length `n` (binary string with only `'0'`s and `'1'`s)

**Rules:**
- If `locked[i] == '1'`: you **cannot** change `s[i]`
- If `locked[i] == '0'`: you **can** change `s[i]` to either `'('` or `')'`

**Task:** Return `true` if you can make `s` a valid parentheses string. Otherwise, return `false`.

### Examples

**Example 1:**
```
Input: s = "))()))", locked = "010100"
Output: true
Explanation: 
- locked[1] == '1' and locked[3] == '1', so we cannot change s[1] or s[3]
- We change s[0] and s[4] to '(' while leaving s[2] and s[5] unchanged
- Result: "(()())" which is valid
```

**Example 2:**
```
Input: s = "()()", locked = "0000"
Output: true
Explanation: s is already valid, no changes needed
```

**Example 3:**
```
Input: s = ")", locked = "0"
Output: false
Explanation: Changing s[0] to either '(' or ')' cannot make it valid
```

**Example 4:**
```
Input: s = "(((())(((())", locked = "111111010111"
Output: true
Explanation: We change s[6] and s[8] to ')' to make s valid
```

### Constraints
- `n == s.length == locked.length`
- `1 <= n <= 10^5`
- `s[i]` is either `'('` or `')'`
- `locked[i]` is either `'0'` or `'1'`

---

## Observations

### Key Insights

1. **Odd Length Strings Cannot Be Valid**
   - Valid parentheses strings must have equal numbers of `'('` and `')'`
   - Therefore, the length must be even
   - If `n` is odd, return `false` immediately

2. **Two Types of Characters**
   - **Locked characters** (`locked[i] == '1'`): Fixed, cannot be changed
   - **Unlocked characters** (`locked[i] == '0'`): Flexible, can be `'('` or `')'`

3. **Greedy Strategy**
   - Process the string from left to right
   - Track unmatched `'('` characters that are locked
   - Track unlocked positions that can be used flexibly
   - Use unlocked positions to balance locked characters when needed

4. **Matching Rules**
   - A locked `'('` needs to be matched with either:
     - A locked `')'` that comes after it
     - An unlocked position that comes after it (convert to `')'`)
   - A locked `')'` needs to be matched with either:
     - A locked `'('` that came before it
     - An unlocked position that came before it (convert to `'('`)

5. **Final Validation**
   - After processing all locked characters, any remaining unlocked positions must be even in count
   - They can pair with each other (half as `'('` and half as `')'`)

---

## Solution

### Algorithm Overview

The solution uses **two stacks** to track:
1. `st_open`: Indices of unmatched locked `'('` characters
2. `st_unlock`: Indices of unlocked positions (can be changed)

### Step-by-Step Process

#### Phase 1: Left-to-Right Scan

```python
for i, c in enumerate(s):
    if locked[i] == '0':
        st_unlock.append(i)  # Store flexible positions
    else:
        if c == '(':
            st_open.append(i)  # Store unmatched locked '('
        else:  # c == ')'
            # Try to match this locked ')' with something before it
            if st_open:
                st_open.pop()  # Match with locked '('
            elif st_unlock:
                st_unlock.pop()  # Use unlocked position as '('
            else:
                return False  # Cannot match this ')'
```

**What happens here:**
- Unlocked positions are saved for later use
- Locked `'('` are tracked as they need matching later
- Locked `')'` are matched immediately with either:
  - Previous locked `'('` (pop from `st_open`)
  - Previous unlocked position (pop from `st_unlock`, convert to `'('`)
  - If neither available, the string is invalid

#### Phase 2: Match Remaining Locked '(' with Unlocked Positions

After the first pass:
- `st_open` contains unmatched locked `'('`
- `st_unlock` contains unused unlocked positions

```python
if st_open and not st_unlock:
    return False  # Unmatched '(' with no flexible positions
```

Try to match each remaining `'('` with an unlocked position **that comes after it**:

```python
while st_open:
    if not st_unlock or st_unlock[-1] < st_open[-1]:
        return False  # No unlocked position after this '('
    st_open.pop()
    st_unlock.pop()  # Use this unlocked position as ')'
```

**Why check `st_unlock[-1] < st_open[-1]`?**
- An unlocked position can only match a `'('` if it comes **after** it
- Since both stacks are in ascending order by index, we compare the tops

#### Phase 3: Check Remaining Unlocked Positions

```python
return not st_open or len(st_unlock) % 2 == 0
```

- If `st_open` is not empty, we failed to match all locked `'('` → return `False`
- Remaining unlocked positions can pair with each other if their count is even
  - Half become `'('`, half become `')'`

### Time Complexity
- **O(n)**: Single pass through the string + matching phase (each element processed once)

### Space Complexity
- **O(n)**: Two stacks can store up to n indices in the worst case

---

## Example Walkthrough

### Example 1: `s = "))()))", locked = "010100"`

**Initial State:**
- `n = 6` (even ✓)

**Left-to-Right Scan:**

| i | s[i] | locked[i] | Action | st_open | st_unlock |
|---|------|-----------|--------|---------|-----------|
| 0 | ')' | '0' | Add to st_unlock | [] | [0] |
| 1 | ')' | '1' | Match with st_unlock[0] | [] | [] |
| 2 | '(' | '0' | Add to st_unlock | [] | [2] |
| 3 | ')' | '1' | Match with st_unlock[2] | [] | [] |
| 4 | ')' | '0' | Add to st_unlock | [] | [4] |
| 5 | ')' | '0' | Add to st_unlock | [] | [4, 5] |

**After Scan:**
- `st_open = []` (no unmatched locked '(')
- `st_unlock = [4, 5]` (2 unlocked positions)
- `len(st_unlock) % 2 == 0` ✓

**Result:** `true`
- Convert s[0] to '(' and s[4] to '(' → `"(()())"`

### Example 4: `s = "(((())(((())", locked = "111111010111"`

**Initial State:**
- `n = 12` (even ✓)

**Left-to-Right Scan:**

| i | s[i] | locked[i] | Action | st_open | st_unlock |
|---|------|-----------|--------|---------|-----------|
| 0-5 | Various | '1' | Track locked '(' and match ')' | [0,1,2] | [] |
| 6 | '(' | '0' | Add to st_unlock | [0,1,2] | [6] |
| 7 | '(' | '1' | Add to st_open | [0,1,2,7] | [6] |
| 8 | '(' | '0' | Add to st_unlock | [0,1,2,7] | [6,8] |
| 9-11 | '(' | '1' | Add to st_open | [0,1,2,7,9,10,11] | [6,8] |

**Matching Phase:**
- Match st_open[11] with st_unlock[8] (8 < 11 ✗, wait...)
- Actually: Match remaining locked '(' with unlocked positions after them
- Use positions 6 and 8 as ')' to match some '('

**Result:** `true`

---

## Code

```python
class Solution:
    def canBeValid(self, s: str, locked: str) -> bool:
        n = len(s)
        # Odd length strings cannot be valid
        if n & 1:
            return False
        
        st_open = []    # Stack for unmatched locked '('
        st_unlock = []  # Stack for unlocked positions
        
        # Phase 1: Left-to-right scan
        for i, c in enumerate(s):
            if locked[i] == '0':
                st_unlock.append(i)
            else:
                if c == '(':
                    st_open.append(i)
                else:  # c == ')'
                    if st_open:
                        st_open.pop()
                    elif st_unlock:
                        st_unlock.pop()
                    else:
                        return False
        
        # Check if we have unlocked positions for remaining '('
        if st_open and not st_unlock:
            return False
        
        # Phase 2: Match remaining locked '(' with unlocked positions
        while st_open:
            if not st_unlock or st_unlock[-1] < st_open[-1]:
                return False
            st_open.pop()
            st_unlock.pop()
        
        # Phase 3: Check if remaining unlocked positions can pair
        return not st_open or len(st_unlock) % 2 == 0
```

# Tags
- Stack
- Greedy
- String
- Parentheses Matching

