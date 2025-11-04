## Problem

https://leetcode.com/problems/backspace-string-compare/description/

```
Given two strings s and t, return true if they are equal when both are typed into empty text editors. '#' means a backspace character.

Note that after backspacing an empty text, the text will continue empty.

Example 1:

Input: s = "ab#c", t = "ad#c"
Output: true
Explanation: Both s and t become "ac".

Example 2:

Input: s = "ab##", t = "c#d#"
Output: true
Explanation: Both s and t become "".

Example 3:

Input: s = "a#c", t = "b"
Output: false
Explanation: s becomes "c" while t becomes "b".

Constraints:

1 <= s.length, t.length <= 200
s and t only contain lowercase letters and '#' characters.
 

Follow up: Can you solve it in O(n) time and O(1) space?
```

## Observations

1. **Backspace Simulation**: The '#' character acts as a backspace, removing the last typed character if one exists.

2. **Stack Behavior**: This problem naturally maps to stack operations:
   - Regular characters → push onto stack
   - '#' character → pop from stack (if not empty)

3. **Final Comparison**: After processing both strings, we compare the final results to determine equality.

4. **Edge Cases**:
   - Backspace on empty text has no effect
   - Multiple consecutive backspaces
   - Strings that become completely empty after processing

5. **Time Complexity**: O(n + m) where n and m are the lengths of strings s and t
   **Space Complexity**: O(n + m) for the two stacks

## Solution

### Approach: Stack Simulation

The solution uses two stacks to simulate the typing process for both strings:

1. **Process String s**:
   - Iterate through each character
   - If character is '#': pop from stack (backspace) if stack is not empty
   - Otherwise: push character onto stack

2. **Process String t**:
   - Same logic as string s using a separate stack

3. **Compare Results**:
   - Join both stacks into strings and compare for equality

### Example Walkthrough:

**Example 1**: s = "ab#c", t = "ad#c"
- Processing s: ['a'] → ['a','b'] → ['a'] → ['a','c'] = "ac"
- Processing t: ['a'] → ['a','d'] → ['a'] → ['a','c'] = "ac"
- Result: "ac" == "ac" → True

**Example 2**: s = "ab##", t = "c#d#" 
- Processing s: ['a'] → ['a','b'] → ['a'] → [] = ""
- Processing t: ['c'] → [] → ['d'] → [] = ""
- Result: "" == "" → True

### Alternative O(1) Space Solution:

For the follow-up question requiring O(1) space, we can use two pointers starting from the end of both strings and compare characters while handling backspaces.

# Tags

- Stack
- String Processing
- Simulation
- Two Pointers (for O(1) space solution)

