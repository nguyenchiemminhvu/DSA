## Problem

https://leetcode.com/problems/remove-outermost-parentheses/description/

```
A valid parentheses string is either empty "", "(" + A + ")", or A + B, where A and B are valid parentheses strings, and + represents string concatenation.

For example, "", "()", "(())()", and "(()(()))" are all valid parentheses strings.
A valid parentheses string s is primitive if it is nonempty, and there does not exist a way to split it into s = A + B, with A and B nonempty valid parentheses strings.

Given a valid parentheses string s, consider its primitive decomposition: s = P1 + P2 + ... + Pk, where Pi are primitive valid parentheses strings.

Return s after removing the outermost parentheses of every primitive string in the primitive decomposition of s.

Example 1:

Input: s = "(()())(())"
Output: "()()()"
Explanation: 
The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
After removing outer parentheses of each part, this is "()()" + "()" = "()()()".

Example 2:

Input: s = "(()())(())(()(()))"
Output: "()()()()(())"
Explanation: 
The input string is "(()())(())(()(()))", with primitive decomposition "(()())" + "(())" + "(()(()))".
After removing outer parentheses of each part, this is "()()" + "()" + "()(())" = "()()()()(())".

Example 3:

Input: s = "()()"
Output: ""
Explanation: 
The input string is "()()", with primitive decomposition "()" + "()".
After removing outer parentheses of each part, this is "" + "" = "".

Constraints:

1 <= s.length <= 105
s[i] is either '(' or ')'.
s is a valid parentheses string.
```

## Observations

1. **Primitive strings**: A primitive parentheses string cannot be split into two non-empty valid parentheses strings. Examples:
   - `"()"` is primitive
   - `"(())"` is primitive  
   - `"()()"` is NOT primitive (can be split into `"()"` + `"()"`)

2. **Key insight**: We need to identify where each primitive string starts and ends, then remove only the outermost parentheses of each primitive string.

3. **Pattern recognition**: 
   - A primitive string always starts with `'('` and ends with `')'`
   - We can use a counter to track the balance of parentheses
   - When counter becomes 0, we've found the end of a primitive string

4. **Algorithm approach**: 
   - Traverse the string while maintaining a balance counter
   - Skip the first `'('` and last `')'` of each primitive string
   - Include all characters in between

## Solution

**Approach: Balance Counter**

The key insight is to use a counter to track the balance of parentheses. When the counter is 0, we're at the boundary between primitive strings.

**Algorithm:**
1. Initialize a result string and a balance counter
2. Iterate through each character in the input string:
   - If it's `'('`:
     - If counter > 0, add it to result (not the outermost opening parenthesis)
     - Increment counter
   - If it's `')'`:
     - Decrement counter
     - If counter > 0, add it to result (not the outermost closing parenthesis)

**Example walkthrough with `"(()())(())"`:**
```
Index: 0 1 2 3 4 5 6 7 8 9 10
Char:  ( ( ) ( ) ) ( ( ) )
Counter after processing: 1 2 1 2 1 0 1 2 1 0

- Index 0: '(' counter=0→1, skip (outermost)
- Index 1: '(' counter=1→2, add to result: "("
- Index 2: ')' counter=2→1, add to result: "()"  
- Index 3: '(' counter=1→2, add to result: "()("
- Index 4: ')' counter=2→1, add to result: "()()"
- Index 5: ')' counter=1→0, skip (outermost)
- Index 6: '(' counter=0→1, skip (outermost)  
- Index 7: '(' counter=1→2, add to result: "()()("
- Index 8: ')' counter=2→1, add to result: "()()()"
- Index 9: ')' counter=1→0, skip (outermost)

Result: "()()()"
```

**Time Complexity:** O(n) - single pass through the string
**Space Complexity:** O(n) - for the result string

**Implementation considerations:**
- The input is guaranteed to be a valid parentheses string
- We only need to track when we're at the outermost level (counter == 0)
- No need to store or identify primitive strings explicitly

# Tags
`String` `Stack` `Parentheses` `Easy`

