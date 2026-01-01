## Problem

https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/description/

Given a string `s` containing `'('`, `')'`, and lowercase English characters, remove the minimum number of parentheses (in any positions) so that the resulting parentheses string is valid and return any valid string.

A parentheses string is valid if and only if:
- It is the empty string, contains only lowercase characters, or
- It can be written as AB (A concatenated with B), where A and B are valid strings, or
- It can be written as (A), where A is a valid string.

### Examples

**Example 1:**
```
Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
```

**Example 2:**
```
Input: s = "a)b(c)d"
Output: "ab(c)d"
```

**Example 3:**
```
Input: s = "))(("
Output: ""
Explanation: An empty string is also valid.
```

### Constraints
- `1 <= s.length <= 10^5`
- `s[i]` is either `'('`, `')'`, or lowercase English letter

## Observations

1. **Valid Parentheses Properties:**
   - Every opening parenthesis `'('` must have a corresponding closing parenthesis `')'` after it
   - Every closing parenthesis `')'` must have a corresponding opening parenthesis `'('` before it
   - Letters don't affect validity and should always be kept

2. **What Makes Parentheses Invalid:**
   - Closing parenthesis `')'` without a preceding unmatched opening parenthesis → must be removed
   - Opening parenthesis `'('` without a following matching closing parenthesis → must be removed

3. **Strategy:**
   - We need to identify which parentheses are unmatched
   - Keep all matched parentheses and all letters
   - Remove only the unmatched parentheses

4. **Stack-Based Matching:**
   - A stack can help track unmatched parentheses
   - When we see `'('`, push its index
   - When we see `')'`:
     - If stack has an unmatched `'('`, pop it (they match)
     - If stack is empty, this `')'` is unmatched
   - After processing all parentheses, anything left in the stack is unmatched

## Solution

### Approach: Two-Pass with Stack

The solution uses a two-pass approach to identify and remove unmatched parentheses.

**Pass 1: Collect Parentheses Indices**
```python
idx = []
for i in range(len(s)):
    if s[i] == '(' or s[i] == ')':
        idx.append(i)
```
- Store indices of all parentheses (both opening and closing)
- This allows us to process only parentheses in the second pass

**Pass 2: Identify Unmatched Parentheses**
```python
st = []
for i in range(len(idx)):
    if s[idx[i]] == ')':
        if st and s[st[-1]] == '(':
            st.pop()  # Matched pair found
        else:
            st.append(idx[i])  # Unmatched ')'
    else:
        st.append(idx[i])  # Unmatched '(' (so far)
```
- Use a stack to track indices of unmatched parentheses
- For each `')'`:
  - If stack top contains `'('`, they match → pop the stack
  - Otherwise, this `')'` is unmatched → push its index
- For each `'('`:
  - Always push its index (might get matched later or remain unmatched)
- After this loop, stack contains indices of all unmatched parentheses

**Pass 3: Build Result**
```python
res = "".join([c for i, c in enumerate(s) if i not in st])
return res
```
- Include all characters whose indices are NOT in the stack
- This removes all unmatched parentheses while keeping matched ones and all letters

### Complete Solution

```python
class Solution:
    def minRemoveToMakeValid(self, s: str) -> str:
        # Pass 1: Collect indices of all parentheses
        idx = []
        for i in range(len(s)):
            if s[i] == '(' or s[i] == ')':
                idx.append(i)
        
        # Pass 2: Identify unmatched parentheses using stack
        st = []
        for i in range(len(idx)):
            if s[idx[i]] == ')':
                if st and s[st[-1]] == '(':
                    st.pop()  # Matched pair
                else:
                    st.append(idx[i])  # Unmatched ')'
            else:
                st.append(idx[i])  # Potentially unmatched '('
        
        # Pass 3: Build result excluding unmatched parentheses
        res = "".join([c for i, c in enumerate(s) if i not in st])
        return res
```

### Complexity Analysis

**Time Complexity:** O(n)
- Pass 1: O(n) to collect parentheses indices
- Pass 2: O(p) where p is number of parentheses, p ≤ n
- Pass 3: O(n) to build result string
- Overall: O(n)

**Space Complexity:** O(n)
- `idx` array: O(p) where p ≤ n
- `st` stack: O(p) in worst case (all unmatched)
- Result string: O(n)
- Overall: O(n)

### Example Walkthrough

**Input:** `s = "lee(t(c)o)de)"`

**Pass 1 - Collect indices:**
```
Indices: 0   1   2   3   4   5   6   7   8   9  10  11  12
String:  l   e   e   (   t   (   c   )   o   )   d   e   )

idx = [3, 5, 7, 9, 12]  # indices of parentheses
```

**Pass 2 - Match parentheses:**
```
i=0: idx[0]=3, s[3]='('  → st=[3]
i=1: idx[1]=5, s[5]='('  → st=[3, 5]
i=2: idx[2]=7, s[7]=')' and s[st[-1]]=s[5]='(' → st=[3] (matched)
i=3: idx[3]=9, s[9]=')' and s[st[-1]]=s[3]='(' → st=[] (matched)
i=4: idx[4]=12, s[12]=')' and st is empty → st=[12] (unmatched)

Final st = [12]  # Index 12 is unmatched
```

**Pass 3 - Build result:**
```
Include all characters except index 12
Result: "lee(t(c)o)de"
```

This matches the expected output!

# Tags

Stack, String, Two-Pass

