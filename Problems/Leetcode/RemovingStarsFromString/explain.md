## Problem

https://leetcode.com/problems/removing-stars-from-a-string/

```
You are given a string s, which contains stars *.

In one operation, you can:

Choose a star in s.
Remove the closest non-star character to its left, as well as remove the star itself.
Return the string after all stars have been removed.

Note:

The input will be generated such that the operation is always possible.
It can be shown that the resulting string will always be unique.

Example 1:

Input: s = "leet**cod*e"
Output: "lecoe"
Explanation: Performing the removals from left to right:
- The closest character to the 1st star is 't' in "leet**cod*e". s becomes "lee*cod*e".
- The closest character to the 2nd star is 'e' in "lee*cod*e". s becomes "lecod*e".
- The closest character to the 3rd star is 'd' in "lecod*e". s becomes "lecoe".
There are no more stars, so we return "lecoe".

Example 2:

Input: s = "erase*****"
Output: ""
Explanation: The entire string is removed, so we return an empty string.

Constraints:

1 <= s.length <= 105
s consists of lowercase English letters and stars *.
The operation above can be performed on s.
```

## Observations

1. **Stack-based approach**: The problem naturally fits a stack data structure since we need to remove the "closest non-star character to the left" of each star.

2. **Left-to-right processing**: We process the string from left to right, which aligns perfectly with stack operations (LIFO - Last In, First Out).

3. **Two operations per character**:
   - If it's a regular character: add it to our result structure
   - If it's a star '*': remove the most recently added character

4. **Guaranteed valid operations**: The problem states that the operation is always possible, meaning we'll never encounter a star when there are no characters to remove.

5. **Linear time complexity**: We process each character exactly once, making this an O(n) solution.

6. **Space optimization**: Using a list as a stack allows us to build the final result directly without additional string concatenation overhead.

## Solution

1. **Initialize an empty stack** (`st = []`) to store characters that survive the removal process.

2. **Iterate through each character** in the input string:
   - **If character is '*'**: Pop the last character from the stack (removes the closest non-star character to the left)
   - **If character is not '*'**: Push the character onto the stack

3. **Convert stack to string**: Join all remaining characters in the stack to form the final result.

**Step-by-step trace for Example 1: `s = "leet**cod*e"`**

| Step | Character | Stack State | Action |
|------|-----------|-------------|---------|
| 1 | 'l' | ['l'] | Append 'l' |
| 2 | 'e' | ['l', 'e'] | Append 'e' |
| 3 | 'e' | ['l', 'e', 'e'] | Append 'e' |
| 4 | 't' | ['l', 'e', 'e', 't'] | Append 't' |
| 5 | '*' | ['l', 'e', 'e'] | Pop 't' |
| 6 | '*' | ['l', 'e'] | Pop 'e' |
| 7 | 'c' | ['l', 'e', 'c'] | Append 'c' |
| 8 | 'o' | ['l', 'e', 'c', 'o'] | Append 'o' |
| 9 | 'd' | ['l', 'e', 'c', 'o', 'd'] | Append 'd' |
| 10 | '*' | ['l', 'e', 'c', 'o'] | Pop 'd' |
| 11 | 'e' | ['l', 'e', 'c', 'o', 'e'] | Append 'e' |

Final result: `"lecoe"`

**Time Complexity:** O(n) - where n is the length of the input string. Each character is processed exactly once.

**Space Complexity:** O(n) - in the worst case (no stars), the stack will contain all characters from the input string.

## Tags

array, string, stack, greedy