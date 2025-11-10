## Problem

https://leetcode.com/problems/make-the-string-great/description/

```
Given a string s of lower and upper case English letters.

A good string is a string which doesn't have two adjacent characters s[i] and s[i + 1] where:

0 <= i <= s.length - 2
s[i] is a lower-case letter and s[i + 1] is the same letter but in upper-case or vice-versa.
To make the string good, you can choose two adjacent characters that make the string bad and remove them. You can keep doing this until the string becomes good.

Return the string after making it good. The answer is guaranteed to be unique under the given constraints.

Notice that an empty string is also good.

Example 1:

Input: s = "leEeetcode"
Output: "leetcode"
Explanation: In the first step, either you choose i = 1 or i = 2, both will result "leEeetcode" to be reduced to "leetcode".

Example 2:

Input: s = "abBAcC"
Output: ""
Explanation: We have many possible scenarios, and all lead to the same answer. For example:
"abBAcC" --> "aAcC" --> "cC" --> ""
"abBAcC" --> "abBA" --> "aA" --> ""

Example 3:

Input: s = "s"
Output: "s"

Constraints:

1 <= s.length <= 100
s contains only lower and upper case English letters.
```

## Observations

1. **Problem Definition**: We need to remove adjacent character pairs where one is lowercase and the other is the same letter in uppercase (or vice versa).

2. **Key Insight**: This is a classic stack problem. When we encounter a character that can form a "bad pair" with the most recent character we've processed, we should remove both characters.

3. **Pattern Recognition**: 
   - Characters like 'a' and 'A' form bad pairs
   - Characters like 'b' and 'B' form bad pairs
   - We only care about adjacent characters

4. **Algorithm Strategy**: 
   - Use a stack to keep track of characters we've processed
   - For each new character, check if it forms a bad pair with the top of the stack
   - If it does, remove the top character (pop) instead of adding the new one
   - If it doesn't, add the new character to the stack

5. **Edge Cases**:
   - Empty string → return empty string
   - Single character → return as is
   - No bad pairs → return original string
   - All characters cancel out → return empty string

## Solution

The solution uses a **stack-based approach**:

### Algorithm Steps:
1. Initialize an empty stack
2. Iterate through each character in the string:
   - If current character is lowercase:
     - Check if stack top is uppercase version of current character
     - If yes, pop from stack (they cancel out)
     - If no, push current character to stack
   - If current character is uppercase:
     - Check if stack top is lowercase version of current character  
     - If yes, pop from stack (they cancel out)
     - If no, push current character to stack
3. Join remaining characters in stack to form result

### Time Complexity: O(n)
- Single pass through the string
- Each character is pushed and popped at most once

### Space Complexity: O(n)
- Stack can hold up to n characters in worst case (no cancellations)

### Example Walkthrough:
For `s = "leEeetcode"`:
- 'l' → stack: ['l']
- 'e' → stack: ['l', 'e'] 
- 'E' → 'E' cancels with 'e' → stack: ['l']
- 'e' → stack: ['l', 'e']
- 'e' → stack: ['l', 'e', 'e']
- 't' → stack: ['l', 'e', 'e', 't']
- 'c' → stack: ['l', 'e', 'e', 't', 'c']
- 'o' → stack: ['l', 'e', 'e', 't', 'c', 'o']
- 'd' → stack: ['l', 'e', 'e', 't', 'c', 'o', 'd']
- 'e' → stack: ['l', 'e', 'e', 't', 'c', 'o', 'd', 'e']

Result: "leetcode"

# Tags

- Stack
- String Manipulation
- Two Pointers (alternative approach)
- Greedy Algorithm

