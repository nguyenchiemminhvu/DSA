## Problem

https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/description/

```
You are given a string s that consists of lower case English letters and brackets.

Reverse the strings in each pair of matching parentheses, starting from the innermost one.

Your result should not contain any brackets.

Example 1:
Input: s = "(abcd)"
Output: "dcba"

Example 2:
Input: s = "(u(love)i)"
Output: "iloveu"
Explanation: The substring "love" is reversed first, then the whole string is reversed.

Example 3:
Input: s = "(ed(et(oc))el)"
Output: "leetcode"
Explanation: First, we reverse the substring "oc", then "etco", and finally, the whole string.

Constraints:
- 1 <= s.length <= 2000
- s only contains lower case English characters and parentheses.
- It is guaranteed that all parentheses are balanced.
```

## Observations

1. **Stack-based approach**: The problem naturally lends itself to a stack-based solution since we need to process nested parentheses from innermost to outermost.

2. **Processing order**: When we encounter a closing parenthesis `)`, we need to reverse everything back to its matching opening parenthesis `(`.

3. **Key insight**: By using a stack, when we pop characters until we find `(`, we get them in **reverse order automatically** due to LIFO (Last In First Out) nature of the stack.

4. **No explicit reversal needed**: We don't need to explicitly reverse and then push back. Simply popping until `(` and pushing back gives us the reversed substring.

5. **Time complexity**: O(n²) in worst case due to nested parentheses requiring multiple passes over substrings.

6. **Space complexity**: O(n) for the stack.

## Solution

### Approach: Stack-Based Processing

```python
class Solution:
    def reverseParentheses(self, s: str) -> str:
        st = []
        for c in s:
            if c == ')':
                # Found closing parenthesis - reverse the substring
                tmp = []
                # Pop characters until we find the matching '('
                while st and st[-1] != '(':
                    tmp.append(st.pop())
                # Remove the opening parenthesis
                st.pop()
                # Push reversed characters back (tmp already has them reversed)
                for ct in tmp:
                    st.append(ct)
            else:
                # Push all other characters (including '(')
                st.append(c)
        
        # Join all characters in the stack to form result
        return "".join(st)
```

### How It Works

**Step-by-step for `s = "(u(love)i)"`:**

1. **Initial**: `st = []`

2. **Process '('**: `st = ['(']`

3. **Process 'u'**: `st = ['(', 'u']`

4. **Process '('**: `st = ['(', 'u', '(']`

5. **Process 'l', 'o', 'v', 'e'**: `st = ['(', 'u', '(', 'l', 'o', 'v', 'e']`

6. **Process ')' (first closing)**:
   - Pop until '(': `tmp = ['e', 'v', 'o', 'l']` (already reversed!)
   - Pop '(': `st = ['(', 'u']`
   - Push tmp back: `st = ['(', 'u', 'e', 'v', 'o', 'l']`

7. **Process 'i'**: `st = ['(', 'u', 'e', 'v', 'o', 'l', 'i']`

8. **Process ')' (second closing)**:
   - Pop until '(': `tmp = ['i', 'l', 'o', 'v', 'e', 'u']` (reversed!)
   - Pop '(': `st = []`
   - Push tmp back: `st = ['i', 'l', 'o', 'v', 'e', 'u']`

9. **Result**: `"iloveu"`

### Why This Works

- The stack's LIFO property means when we pop characters, we get them in reverse order
- By immediately pushing them back, we've effectively reversed that segment
- Nested parentheses are handled naturally because inner ones are processed first
- The opening parentheses act as markers/delimiters for where to stop reversing

### Complexity Analysis

- **Time Complexity**: O(n²) where n is the length of the string
  - In worst case (deeply nested parentheses), we might process each character multiple times
  - Example: `"((((a))))"` requires multiple reversals
  
- **Space Complexity**: O(n)
  - Stack can hold up to n characters
  - The temporary list `tmp` is reused and contains at most n characters

# Tags

`Stack` `String` `Simulation` `String Manipulation` `Parentheses Processing`

