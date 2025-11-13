## Problem

https://leetcode.com/problems/substring-matching-pattern/description/

```
You are given a string s and a pattern string p, where p contains exactly one '*' character.

The '*' in p can be replaced with any sequence of zero or more characters.

Return true if p can be made a substring of s, and false otherwise.

Example 1:

Input: s = "leetcode", p = "ee*e"

Output: true

Explanation:

By replacing the '*' with "tcod", the substring "eetcode" matches the pattern.

Example 2:

Input: s = "car", p = "c*v"

Output: false

Explanation:

There is no substring matching the pattern.

Example 3:

Input: s = "luck", p = "u*"

Output: true

Explanation:

The substrings "u", "uc", and "uck" match the pattern.

Constraints:

1 <= s.length <= 50
1 <= p.length <= 50 
s contains only lowercase English letters.
p contains only lowercase English letters and exactly one '*'
```

## Observations

1. **Pattern Structure**: The pattern `p` has exactly one '*' character that can be replaced with any sequence of zero or more characters. This splits the pattern into two parts:
   - `p1`: The prefix before '*' 
   - `p2`: The suffix after '*'

2. **Substring Matching**: We need to find if there exists a substring in `s` that matches the pattern when '*' is replaced with some characters.

3. **Key Insight**: For a valid match, we need to find:
   - An occurrence of `p1` in `s`
   - An occurrence of `p2` in `s` that comes after the found `p1`
   - The `p2` must start at or after position `found_p1 + len(p1)`

4. **Edge Cases**:
   - If `p1` is empty (pattern starts with '*'), we start searching from position 0
   - If `p2` is empty (pattern ends with '*'), we only need to find `p1`
   - The '*' can match zero characters, so `p2` can immediately follow `p1`

5. **Sequential Search**: Since we need `p1` to appear before `p2`, we search for them sequentially rather than independently.

## Solution

### Approach: Two-Phase String Search

The solution splits the pattern at the '*' character and performs sequential string matching:

#### Algorithm Steps:

1. **Split Pattern**: Find the '*' position and split pattern into prefix (`p1`) and suffix (`p2`)

2. **Search for Prefix**: 
   - If `p1` is empty, start from position 0
   - Otherwise, find the first occurrence of `p1` in `s`
   - If not found, return False

3. **Search for Suffix**:
   - Start searching for `p2` from position `found_p1_position + len(p1)`
   - This ensures `p2` comes after `p1` (or at the same position if '*' matches zero characters)
   - If not found, return False

4. **Return Result**: If both parts are found in the correct order, return True

#### Example Walkthrough:

**Example 1**: `s = "leetcode"`, `p = "ee*e"`
- `p1 = "ee"`, `p2 = "e"`
- Find "ee" in "leetcode" → found at index 1
- Search for "e" starting from index 1+2=3 → found at index 7
- Both found in correct order → Return True

**Example 2**: `s = "car"`, `p = "c*v"`
- `p1 = "c"`, `p2 = "v"`  
- Find "c" in "car" → found at index 0
- Search for "v" starting from index 0+1=1 → not found
- Return False

**Example 3**: `s = "luck"`, `p = "u*"`
- `p1 = "u"`, `p2 = ""`
- Find "u" in "luck" → found at index 1
- `p2` is empty, so no second search needed → Return True

#### Time & Space Complexity:

- **Time Complexity**: O(n×m) where n = len(s), m = len(p)
  - `find()` operations can take O(n×m) in worst case
  - Two sequential searches at most

- **Space Complexity**: O(1) 
  - Only storing indices and substring references
  - No additional data structures needed

#### Alternative Approaches:

1. **Regex Matching**: Convert pattern to regex and use pattern matching
2. **Dynamic Programming**: Use 2D DP for more complex pattern matching
3. **KMP Algorithm**: For more efficient string searching in larger inputs

# Tags

- String
- Pattern Matching  
- String Search
- Two Pointers
- Substring

**Difficulty**: Medium
**Companies**: Google, Amazon, Microsoft
**Similar Problems**: 
- Wildcard Matching (LeetCode 44)
- Regular Expression Matching (LeetCode 10)
- Implement strStr() (LeetCode 28)

