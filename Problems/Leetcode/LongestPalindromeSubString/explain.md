## Problem

https://leetcode.com/problems/longest-palindromic-substring/description/

```
Given a string s, return the longest palindromic substring in s.

Example 1:

Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Example 2:

Input: s = "cbbd"
Output: "bb"

Constraints:

1 <= s.length <= 1000
s consist of only digits and English letters.
```

## Observations

1. **Palindrome Properties**: A palindrome reads the same forwards and backwards. For a substring to be a palindrome:
   - Single characters are always palindromes
   - Two identical adjacent characters form palindromes
   - Longer palindromes can be formed by extending shorter palindromes with matching characters on both ends

2. **Dynamic Programming Approach**: The solution uses bottom-up DP where:
   - We start with base cases (length 1 and 2 palindromes)
   - Build longer palindromes by extending existing ones
   - Use memoization to store valid palindrome ranges

3. **State Representation**: Each palindrome is represented as a tuple `(left_index, right_index)` stored in a set for O(1) lookup

4. **Building Strategy**: 
   - Initialize all single characters as palindromes
   - Check for adjacent identical characters (length 2 palindromes)
   - For longer lengths, extend existing palindromes by checking if outer characters match

## Solution

1. **Initialization (Base Cases)**:
   - Add all single characters `(i, i)` as palindromes
   - Check adjacent characters and add `(i-1, i)` if they match

2. **Dynamic Programming Loop**:
   - `cur_len`: Current length we're trying to build (2 to n-1)
   - `i`: End position of the potential palindrome
   - `l = i - cur_len`: Start position of the potential palindrome
   - Check if `(l+1, r-1)` exists in memo (inner substring is palindrome)
   - Check if `s[l] == s[r]` (outer characters match)

3. **Result Extraction**:
   - Iterate through all stored palindromes
   - Find the one with maximum length
   - Extract the substring using stored indices

### Time & Space Complexity

- **Time Complexity**: O(n²)
  - Nested loops iterate through all possible substrings
  - Set lookup is O(1)
  
- **Space Complexity**: O(n²)
  - In worst case, all substrings could be palindromes
  - Set stores at most O(n²) tuples

### Example Walkthrough

For `s = "babad"`:

1. **Base cases**: `{(0,0), (1,1), (2,2), (3,3), (4,4)}`
2. **Length 2**: No adjacent identical characters
3. **Length 3**: 
   - Check `(0,2)`: `s[0]='b', s[2]='b'` and `(1,1)` exists → Add `(0,2)`
   - Check `(1,3)`: `s[1]='a', s[3]='a'` and `(2,2)` exists → Add `(1,3)`
4. **Length 4**: No valid extensions
5. **Result**: Both `"bab"` and `"aba"` have length 3, return either one

### Alternative Approaches

1. **Expand Around Centers**: O(n²) time, O(1) space
2. **Manacher's Algorithm**: O(n) time, O(n) space
3. **Brute Force**: O(n³) time, O(1) space

This DP solution provides a good balance of clarity and efficiency.

## Tags

array, string, dynamic programming