## Problem

https://leetcode.com/problems/reformat-the-string/

```
You are given an alphanumeric string s. (Alphanumeric string is a string consisting of lowercase English letters and digits).

You have to find a permutation of the string where no letter is followed by another letter and no digit is followed by another digit. That is, no two adjacent characters have the same type.

Return the reformatted string or return an empty string if it is impossible to reformat the string.

Example 1:
Input: s = "a0b1c2"
Output: "0a1b2c"
Explanation: No two adjacent characters have the same type in "0a1b2c". "a0b1c2", "0a1b2c", "0c2a1b" are also valid permutations.

Example 2:
Input: s = "leetcode"
Output: ""
Explanation: "leetcode" has only characters so we cannot separate them by digits.

Example 3:
Input: s = "1229857369"
Output: ""
Explanation: "1229857369" has only digits so we cannot separate them by characters.

Constraints:
- 1 <= s.length <= 500
- s consists of only lowercase English letters and/or digits.
```

## Observations

1. **Character Separation**: We need to separate digits and letters into two groups
2. **Alternating Pattern**: The result must alternate between digits and letters
3. **Impossibility Condition**: If the difference between the count of digits and letters is more than 1, it's impossible to create an alternating pattern
4. **Edge Cases**: 
   - All digits: impossible (no letters to alternate)
   - All letters: impossible (no digits to alternate)
   - Equal counts: can start with either type
   - Difference of 1: must start with the more frequent type

## Solution

1. **Separation Phase**: Split the input string into two arrays - one for digits (`a`) and one for letters (`b`)

2. **Feasibility Check**: If `|len(a) - len(b)| > 1`, it's impossible to create an alternating pattern, so return empty string

3. **Alternating Construction**: Build the result by alternating characters from both arrays for the minimum length

4. **Handle Remainder**: If one array has exactly one more character:
   - If more letters: prepend the extra letter to ensure alternating pattern
   - If more digits: append the extra digit to the end

**Time Complexity**: O(n) where n is the length of string s
**Space Complexity**: O(n) for storing the separated characters

**Key Insight**: The algorithm ensures that no two adjacent characters are of the same type by carefully managing the placement of the extra character when counts differ by 1.

# Tags
- String Manipulation
- Two Pointers
- Greedy Algorithm

