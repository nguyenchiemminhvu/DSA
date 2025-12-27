## Problem

https://leetcode.com/problems/minimum-string-length-after-balanced-removals/description/

```
You are given a string s consisting only of the characters 'a' and 'b'.

You are allowed to repeatedly remove any substring where the number of 'a' 
characters is equal to the number of 'b' characters. After each removal, the 
remaining parts of the string are concatenated together without gaps.

Return an integer denoting the minimum possible length of the string after 
performing any number of such operations.

Example 1:
Input: s = "aabbab"
Output: 0
Explanation: The substring "aabbab" has three 'a' and three 'b'. Since their 
counts are equal, we can remove the entire string directly.

Example 2:
Input: s = "aaaa"
Output: 4
Explanation: Every substring of "aaaa" contains only 'a' characters. No substring 
can be removed as a result, so the minimum length remains 4.

Example 3:
Input: s = "aaabb"
Output: 1
Explanation: First, remove the substring "ab", leaving "aab". Next, remove the 
new substring "ab", leaving "a". No further removals are possible.

Constraints:
- 1 <= s.length <= 10^5
- s[i] is either 'a' or 'b'
```

## Observations

1. **Key Insight**: We can remove any substring where count('a') == count('b'). This means we can greedily match and remove adjacent opposite characters.

2. **Greedy Approach**: Instead of finding all possible balanced substrings, we can use a simpler strategy - match adjacent opposite characters and remove them immediately. This works because:
   - Any balanced substring can be reduced to a sequence of adjacent pair removals
   - If we have "ab" or "ba", they can be removed
   - After removal, new adjacent pairs might form, which we can continue removing

3. **Stack Pattern**: This is similar to parentheses matching problems. We use a stack where:
   - Characters that can pair up with the stack top are removed (both popped)
   - Characters that can't pair up are pushed to the stack

4. **Final State**: After all possible removals, the remaining string will have an excess of either 'a's or 'b's (or both types that can't be balanced further). The minimum length is the absolute difference between the counts.

## Solution

**Approach**: Stack-based greedy matching

**Algorithm**:
1. Use a stack to track unmatched characters
2. For each character in the string:
   - If it's opposite to the top of the stack, pop the stack (they form a balanced pair)
   - Otherwise, push the character to the stack
3. The remaining stack size is the minimum possible length

**Why it works**:
- When we see 'a' followed by 'b' (or vice versa), we can immediately remove them
- This greedy removal is optimal because removing pairs earlier doesn't prevent any future removals
- The characters left in the stack are those that couldn't find a matching opposite character

**Time Complexity**: O(n) - single pass through the string
**Space Complexity**: O(n) - stack in worst case (all same characters)

```python
class Solution:
    def minLengthAfterRemovals(self, s: str) -> int:
        st = []
        for c in s:
            if c == 'b':
                if st and st[-1] == 'a':
                    st.pop()  # Remove the matching 'a'
                else:
                    st.append(c)  # No match, add 'b'
            else:  # c == 'a'
                if st and st[-1] == 'b':
                    st.pop()  # Remove the matching 'b'
                else:
                    st.append(c)  # No match, add 'a'
        return len(st)
```

**Alternative simpler implementation**:
```python
class Solution:
    def minLengthAfterRemovals(self, s: str) -> int:
        st = []
        for c in s:
            # If stack is not empty and top is opposite character, pop
            if st and st[-1] != c:
                st.pop()
            else:
                st.append(c)
        return len(st)
```

**Example walkthrough** for s = "aaabb":
- Process 'a': stack = ['a']
- Process 'a': stack = ['a', 'a']
- Process 'a': stack = ['a', 'a', 'a']
- Process 'b': top is 'a' (opposite), pop → stack = ['a', 'a']
- Process 'b': top is 'a' (opposite), pop → stack = ['a']
- Result: 1 (one 'a' remaining)

# Tags
#stack #greedy #string #two-pointer #balance-matching

