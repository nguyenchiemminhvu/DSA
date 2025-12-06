## Problem

https://leetcode.com/problems/replace-all-s-to-avoid-consecutive-repeating-characters/description/

```
Given a string s containing only lowercase English letters and the '?' character, convert all the '?' characters into lowercase letters such that the final string does not contain any consecutive repeating characters. You cannot modify the non '?' characters.

It is guaranteed that there are no consecutive repeating characters in the given string except for '?'.

Return the final string after all the conversions (possibly zero) have been made. If there is more than one solution, return any of them. It can be shown that an answer is always possible with the given constraints.

Example 1:
Input: s = "?zs"
Output: "azs"
Explanation: There are 25 solutions for this problem. From "azs" to "yzs", all are valid. Only "z" is an invalid modification as the string will consist of consecutive repeating characters in "zzs".

Example 2:
Input: s = "ubv?w"
Output: "ubvaw"
Explanation: There are 24 solutions for this problem. Only "v" and "w" are invalid modifications as the strings will consist of consecutive repeating characters in "ubvvw" and "ubvww".

Constraints:
- 1 <= s.length <= 100
- s consist of lowercase English letters and '?'.
```

## Observations

1. **Input Constraints**: The string contains only lowercase letters and '?' characters, with no consecutive repeating characters initially (except '?').

2. **Goal**: Replace each '?' with a lowercase letter such that no two consecutive characters are the same.

3. **Key Insight**: For any position with '?', we only need to check its immediate neighbors (left and right) to ensure the replacement doesn't create consecutive repeating characters.

4. **Guaranteed Solution**: Since there are 26 lowercase letters and at most 2 neighbors to avoid (left and right), we always have at least 24 valid choices for each '?'.

5. **Greedy Approach**: We can process the string from left to right, replacing each '?' as we encounter it. Once a '?' is replaced, it becomes fixed and serves as a constraint for subsequent '?' characters.

6. **Boundary Handling**: The first and last characters have only one neighbor to check, making them easier cases.

## Solution

### Approach: Greedy Replacement with Sentinel Characters

The solution uses a clever technique of adding sentinel characters ('#') at both ends of the string to simplify boundary checking.

**Algorithm:**
1. Add sentinel characters '#' at the beginning and end of the string
2. Convert the string to a list for mutability
3. Iterate through each character (excluding sentinels)
4. For each '?' character:
   - Try each lowercase letter from 'a' to 'z'
   - Find the first letter that differs from both the previous and next characters
   - Replace '?' with this letter and break
5. Build the result string without the sentinel characters

**Why it works:**
- By adding sentinels, we eliminate special cases for boundary checking
- Each '?' only needs to avoid its immediate neighbors
- The greedy approach works because:
  - We process left to right, so previous '?' are already resolved
  - Each position has at least 24 valid choices (26 letters - 2 neighbors)
  - Future positions won't affect current decisions

**Time Complexity:** O(n * 26) = O(n), where n is the length of the string
- We iterate through each character once
- For each '?', we check at most 26 letters (in practice, usually just 1-3)

**Space Complexity:** O(n)
- We create a list copy of the string with 2 additional sentinel characters
- The result string also requires O(n) space

**Example Walkthrough:**

For `s = "?zs"`:
1. After adding sentinels: `"#?zs#"`
2. Index 1 (i=1): '?' → Check neighbors '#' and 'z' → Choose 'a' → `"#azs#"`
3. Index 2 (i=2): 'z' → Keep as is
4. Index 3 (i=3): 's' → Keep as is
5. Result: `"azs"`

For `s = "ubv?w"`:
1. After adding sentinels: `"#ubv?w#"`
2. Process 'u', 'b', 'v' normally
3. Index 4 (i=4): '?' → Check neighbors 'v' and 'w' → Choose 'a' (first valid) → `"#ubvaw#"`
4. Process 'w' normally
5. Result: `"ubvaw"`

# Tags

`String` `Greedy` `Array`

