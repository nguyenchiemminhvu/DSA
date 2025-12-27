## Problem

https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/description/

```
A parentheses string is valid if and only if:
- It is the empty string,
- It can be written as AB (A concatenated with B), where A and B are valid strings, or
- It can be written as (A), where A is a valid string.

You are given a parentheses string s. In one move, you can insert a parenthesis at any position of the string.

For example, if s = "()))", you can insert an opening parenthesis to be "(()))" or a closing parenthesis to be "())))".

Return the minimum number of moves required to make s valid.

Example 1:
Input: s = "())"
Output: 1

Example 2:
Input: s = "((("
Output: 3

Constraints:
- 1 <= s.length <= 1000
- s[i] is either '(' or ')'.
```

## Observations

1. **Valid Parentheses Matching**: A valid parentheses string requires each opening parenthesis '(' to have a corresponding closing parenthesis ')' that comes after it.

2. **Two Types of Imbalances**:
   - **Unmatched closing parentheses**: When we encounter ')' but there's no corresponding '(' before it
   - **Unmatched opening parentheses**: When we have '(' that never gets closed

3. **Stack-Based Tracking**: We can use a stack to track unmatched opening parentheses:
   - Push '(' onto the stack
   - Pop from stack when we see ')' (if stack is not empty)
   - If stack is empty when we see ')', we have an unmatched ')'

4. **Final Count**: 
   - Count of unmatched ')' = number of times we encounter ')' with empty stack
   - Count of unmatched '(' = remaining elements in stack at the end
   - Total moves = unmatched ')' + unmatched '('

## Solution

```python
class Solution:
    def minAddToMakeValid(self, s: str) -> int:
        st = []
        count = 0
        for c in s:
            if c == '(':
                st.append(c)
            else:
                if not st:
                    count += 1
                else:
                    st.pop()
        return count + len(st)
```

**Algorithm Explanation**:

1. **Initialize Variables**:
   - `st`: Stack to track unmatched opening parentheses '('
   - `count`: Counter for unmatched closing parentheses ')'

2. **Process Each Character**:
   - If character is '(':
     - Push it onto the stack (potential opening that needs matching)
   - If character is ')':
     - If stack is empty: Increment `count` (no matching '(' available)
     - If stack is not empty: Pop from stack (successfully matched with a '(')

3. **Calculate Result**:
   - `count`: Number of ')' that had no matching '(' before them
   - `len(st)`: Number of '(' that never got matched with a ')'
   - Return their sum as the minimum insertions needed

**Example Walkthrough** (s = "())"):
- Process '(': stack = ['('], count = 0
- Process ')': stack = [], count = 0 (matched and popped)
- Process ')': stack = [], count = 1 (no '(' to match)
- Result: count + len(st) = 1 + 0 = 1

**Time Complexity**: O(n) where n is the length of the string  
**Space Complexity**: O(n) for the stack in worst case (all opening parentheses)

# Tags

