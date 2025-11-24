## Problem

https://leetcode.com/problems/existence-of-a-substring-in-a-string-and-its-reverse/

```
Given a string s, find any substring of length 2 which is also present in the reverse of s.

Return true if such a substring exists, and false otherwise.

Example 1:

Input: s = "leetcode"

Output: true

Explanation: Substring "ee" is of length 2 which is also present in reverse(s) == "edocteel".

Example 2:

Input: s = "abcba"

Output: true

Explanation: All of the substrings of length 2 "ab", "bc", "cb", "ba" are also present in reverse(s) == "abcba".

Example 3:

Input: s = "abcd"

Output: false

Explanation: There is no substring of length 2 in s, which is also present in the reverse of s.

Constraints:

1 <= s.length <= 100
s consists only of lowercase English letters.
```

## Observations

1. **Problem Requirements**: We need to find if any substring of length 2 from the original string `s` also exists in the reverse of `s`.

2. **Key Insights**:
   - We only need to check substrings of exactly length 2
   - The substring must appear in both the original string and its reverse
   - If string length is 1, no substring of length 2 exists, so return False
   - For a palindromic substring of length 2 (like "aa"), it will always exist in both string and its reverse

3. **Approach Analysis**:
   - Brute force: Generate all length-2 substrings and check if each exists in the reversed string
   - Time complexity: O(n²) where n is the length of string
   - Space complexity: O(n) for storing the reversed string

4. **Edge Cases**:
   - String length 1: No substring of length 2 possible → False
   - String with identical adjacent characters (e.g., "aa"): Always True
   - Palindromic strings: Likely to have matching substrings

## Solution

1. **Reverse the string**: Create `rev_s = s[::-1]` to get the reversed version of the input string.

2. **Iterate through all possible length-2 substrings**: 
   - Loop from index 1 to len(s)-1
   - For each position i, extract substring `s[i-1:i+1]` (2 characters starting from i-1)

3. **Check existence in reverse**: 
   - Use Python's `in` operator to check if the current substring exists anywhere in `rev_s`
   - The `in` operator performs substring search efficiently

4. **Early termination**: 
   - Return `True` immediately when first matching substring is found
   - Return `False` only if no matching substring is found after checking all possibilities

**Example Walkthrough**:

For `s = "leetcode"`:
- `rev_s = "edocteel"`
- Substrings checked: "le", "ee", "et", "tc", "co", "od", "de"
- "ee" exists in "edocteel" → return `True`

For `s = "abcd"`:
- `rev_s = "dcba"`
- Substrings checked: "ab", "bc", "cd"
- None of these exist in "dcba" → return `False`

**Time Complexity**: O(n²) - For each of the n-1 substrings, we perform substring search in reverse string
**Space Complexity**: O(n) - For storing the reversed string

# Tags
- String Manipulation
- Substring Search  
- Two Pointers
- Brute Force

