## Problem

https://leetcode.com/problems/delete-characters-to-make-fancy-string/

```
A fancy string is a string where no three consecutive characters are equal.

Given a string s, delete the minimum possible number of characters from s to make it fancy.

Return the final string after the deletion. It can be shown that the answer will always be unique.

Example 1:

Input: s = "leeetcode"
Output: "leetcode"
Explanation:
Remove an 'e' from the first group of 'e's to create "leetcode".
No three consecutive characters are equal, so return "leetcode".
Example 2:

Input: s = "aaabaaaa"
Output: "aabaa"
Explanation:
Remove an 'a' from the first group of 'a's to create "aabaaaa".
Remove two 'a's from the second group of 'a's to create "aabaa".
No three consecutive characters are equal, so return "aabaa".

Example 3:

Input: s = "aab"
Output: "aab"
Explanation: No three consecutive characters are equal, so return "aab".

Constraints:

1 <= s.length <= 105
s consists only of lowercase English letters.
```

## Observations

1. **Goal**: Remove minimum characters to ensure no three consecutive characters are equal
2. **Key insight**: We can keep at most 2 consecutive identical characters
3. **Greedy approach**: Process characters sequentially and only add to result if it doesn't create 3 consecutive identical characters
4. **Counter tracking**: Need to track how many consecutive identical characters we've seen
5. **Linear solution**: Single pass through the string is sufficient

## Solution

### Approach: Greedy with Counter Tracking

The solution uses a greedy approach with the following strategy:

1. **Initialize tracking variables**:
   - `count`: Tracks consecutive occurrences of current character
   - `res`: Result list to build the fancy string
   - `prev`: Previous character (initialized to '#' to handle first character)

2. **Process each character**:
   - If current character equals previous character: increment count
   - If different character: reset count to 1
   - Only add character to result if count < 3 (allows at most 2 consecutive)
   - Update previous character

3. **Return result**: Join the result list into a string

### Algorithm Walkthrough

For input `s = "aaabaaaa"`:
- Process 'a': count=1, add to res → res=['a']
- Process 'a': count=2, add to res → res=['a','a'] 
- Process 'a': count=3, skip (don't add) → res=['a','a']
- Process 'b': count=1, add to res → res=['a','a','b']
- Process 'a': count=1, add to res → res=['a','a','b','a']
- Process 'a': count=2, add to res → res=['a','a','b','a','a']
- Process 'a': count=3, skip → res=['a','a','b','a','a']
- Process 'a': count=4, skip → res=['a','a','b','a','a']

Result: "aabaa"

### Complexity Analysis
- **Time Complexity**: O(n) - single pass through the string
- **Space Complexity**: O(n) - for the result list (excluding output space)

### Key Insights
- Greedy works because we never need to "look ahead" - keeping at most 2 consecutive characters is always optimal
- The counter reset mechanism elegantly handles transitions between different characters
- Using a dummy initial character ('#') simplifies the logic for the first character

# Tags

String, Greedy, Two Pointers

