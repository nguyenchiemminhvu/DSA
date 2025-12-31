## Problem

https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/description/

```
Given a string s, determine if it is valid.

A string s is valid if, starting with an empty string t = "", you can transform t into s 
after performing the following operation any number of times:

- Insert string "abc" into any position in t. More formally, t becomes tleft + "abc" + tright, 
  where t == tleft + tright. Note that tleft and tright may be empty.

Return true if s is a valid string, otherwise, return false.

Example 1:
Input: s = "aabcbc"
Output: true
Explanation:
"" -> "abc" -> "aabcbc"
Thus, "aabcbc" is valid.

Example 2:
Input: s = "abcabcababcc"
Output: true
Explanation:
"" -> "abc" -> "abcabc" -> "abcabcabc" -> "abcabcababcc"
Thus, "abcabcababcc" is valid.

Example 3:
Input: s = "abccba"
Output: false
Explanation: It is impossible to get "abccba" using the operation.

Constraints:
- 1 <= s.length <= 2 * 10^4
- s consists of letters 'a', 'b', and 'c'
```

## Observations

1. **Building vs. Removing "abc"**: Instead of thinking about building the string by inserting "abc", 
   we can think backwards - a valid string should allow us to repeatedly remove "abc" substrings 
   until we're left with an empty string.

2. **Stack Matching Pattern**: This is similar to matching parentheses. We need to match the pattern 
   "abc" where:
   - 'a' is like an opening bracket
   - 'b' is like a middle element
   - 'c' is like a closing bracket that completes the pattern

3. **Order Matters**: The characters must appear in the exact order 'a', 'b', 'c'. When we see 'c', 
   we must have 'b' and 'a' immediately before it (in the stack).

4. **Stack Solution**: Use a stack to track characters:
   - Push 'a' and 'b' onto the stack
   - When we see 'c', check if the top two elements are 'b' and 'a' (in that order from top)
   - If yes, pop them both (removing one "abc" pattern)
   - If no, the string is invalid
   - At the end, the stack must be empty

## Solution

```python
class Solution:
    def isValid(self, s: str) -> bool:
        st = []
        for c in s:
            if c == 'c':
                # When we see 'c', we need 'b' and 'a' before it
                if len(st) >= 2 and st[-1] == 'b' and st[-2] == 'a':
                    st.pop()  # Remove 'b'
                    st.pop()  # Remove 'a'
                    # We've successfully matched and removed one "abc" pattern
                else:
                    # 'c' appeared without proper 'ab' prefix
                    return False
            else:
                # For 'a' or 'b', just add to stack
                st.append(c)
        
        # Valid string must have consumed all characters (empty stack)
        return not st
```

**How it works:**

1. **Process each character**: Iterate through the string character by character.

2. **For 'a' or 'b'**: Simply push onto the stack, waiting for their matching 'c'.

3. **For 'c'**: This is the key moment - 'c' should complete an "abc" pattern.
   - Check if the last two characters in the stack are 'b' (top) and 'a' (second from top)
   - If yes, pop both - we've found and removed one complete "abc"
   - If no, the string is invalid because 'c' appeared without its proper prefix

4. **Final check**: After processing all characters, the stack must be empty. Any remaining 
   characters mean we have incomplete "abc" patterns.

**Example walkthrough** for `s = "aabcbc"`:
```
c='a': stack = ['a']
c='a': stack = ['a', 'a']
c='b': stack = ['a', 'a', 'b']
c='c': stack[-1]='b', stack[-2]='a' ✓ -> pop twice -> stack = ['a']
c='b': stack = ['a', 'b']
c='c': stack[-1]='b', stack[-2]='a' ✓ -> pop twice -> stack = []
Result: stack is empty ✓ -> return true
```

**Time Complexity**: O(n) where n is the length of the string - we process each character once.

**Space Complexity**: O(n) in the worst case for the stack (e.g., string with only 'a' and 'b' characters).

# Tags

Stack, String, Pattern Matching

