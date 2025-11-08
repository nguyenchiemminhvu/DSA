## Problem

https://leetcode.com/problems/clear-digits/description/

```
You are given a string s.

Your task is to remove all digits by doing this operation repeatedly:

Delete the first digit and the closest non-digit character to its left.
Return the resulting string after removing all digits.

Note that the operation cannot be performed on a digit that does not have any non-digit character to its left.

Example 1:

Input: s = "abc"

Output: "abc"

Explanation:

There is no digit in the string.

Example 2:

Input: s = "cb34"

Output: ""

Explanation:

First, we apply the operation on s[2], and s becomes "c4".

Then we apply the operation on s[1], and s becomes "".

Constraints:

1 <= s.length <= 100
s consists only of lowercase English letters and digits.
The input is generated such that it is possible to delete all digits.
```

## Observations

1. **Stack-based approach**: When we encounter a digit, we need to remove the closest non-digit character to its left. This suggests using a stack data structure.

2. **Left-to-right processing**: We process the string from left to right, maintaining valid characters in our stack.

3. **Digit removal logic**: When we encounter:
   - A non-digit character: Add it to our stack (it might be removed later by a digit)
   - A digit: Remove the most recently added non-digit character (top of stack)

4. **Guaranteed solvability**: The problem states that the input guarantees all digits can be removed, meaning there will always be enough non-digit characters to the left of each digit.

5. **Time complexity**: O(n) where n is the length of the string - we process each character once.

6. **Space complexity**: O(n) in worst case where we store all characters in the stack.

## Solution

1. **Initialize**: Create an empty stack `st` to store valid characters.

2. **Iterate through string**: For each character `c` in the input string:
   - If `c` is a digit: Pop the top element from the stack (this removes the closest non-digit character to the left)
   - If `c` is not a digit: Push it onto the stack

3. **Return result**: Join all remaining characters in the stack to form the final string.

**Step-by-step example with "cb34":**
- Process 'c': stack = ['c']
- Process 'b': stack = ['c', 'b']  
- Process '3': stack = ['c'] (removes 'b')
- Process '4': stack = [] (removes 'c')
- Result: ""

**Step-by-step example with "abc2d1":**
- Process 'a': stack = ['a']
- Process 'b': stack = ['a', 'b']
- Process 'c': stack = ['a', 'b', 'c']
- Process '2': stack = ['a', 'b'] (removes 'c')
- Process 'd': stack = ['a', 'b', 'd']
- Process '1': stack = ['a', 'b'] (removes 'd')
- Result: "ab"

# Tags

- Stack
- String Manipulation
- Simulation

