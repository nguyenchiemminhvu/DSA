## Problem

https://leetcode.com/problems/unique-length-3-palindromic-subsequences/description/

```
Given a string s, return the number of unique palindromes of length three that are a subsequence of s.

Note that even if there are multiple ways to obtain the same subsequence, it is still only counted once.

A palindrome is a string that reads the same forwards and backwards.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".

Example 1:

Input: s = "aabca"
Output: 3
Explanation: The 3 palindromic subsequences of length 3 are:
- "aba" (subsequence of "aabca")
- "aaa" (subsequence of "aabca")
- "aca" (subsequence of "aabca")

Example 2:

Input: s = "adc"
Output: 0
Explanation: There are no palindromic subsequences of length 3 in "adc".

Example 3:

Input: s = "bbcbaba"
Output: 4
Explanation: The 4 palindromic subsequences of length 3 are:
- "bbb" (subsequence of "bbcbaba")
- "bcb" (subsequence of "bbcbaba")
- "bab" (subsequence of "bbcbaba")
- "aba" (subsequence of "bbcbaba")

Constraints:

3 <= s.length <= 105
s consists of only lowercase English letters.
```

## Observations

1. **Palindrome Structure**: For a length-3 palindrome, the pattern is `XYX` where the first and last characters must be the same.

2. **Key Insight**: For each character `c`, we need to find:
   - The **first** occurrence of `c` in the string
   - The **last** occurrence of `c` in the string
   - All **unique** characters between these two positions

3. **Counting Strategy**: If character `c` appears at positions `i` and `j` (where `i < j`), then the number of unique palindromes starting and ending with `c` equals the number of unique characters between positions `i+1` and `j-1`.

4. **Edge Cases**: 
   - If a character appears only once, it cannot form a length-3 palindrome
   - If a character appears exactly twice, palindromes depend on what's between them
   - Characters that appear more than twice: we only consider first and last occurrence

5. **Efficiency Considerations**:
   - We only need to track first and last occurrence of each character
   - Using a set to count unique characters between boundaries ensures O(1) lookup per character
   - Time complexity: O(n) for scanning + O(26 × n) for counting = O(n)

## Solution

The solution uses a clever two-pass approach:

### Algorithm Steps:

1. **First Pass - Find Boundaries**: 
   - Create a `prefix` array to store `[first_index, last_index]` for each of the 26 lowercase letters
   - Scan through the string once to populate these boundaries

2. **Second Pass - Count Unique Palindromes**:
   - For each character in the alphabet (`a` to `z`)
   - If the character has both first and last positions (appears at least twice)
   - Count unique characters between `first_position + 1` and `last_position - 1`
   - Add this count to the total

### Code Breakdown:

For `s = "aabca"`:
- Character `'a'`: first=0, last=4, between chars = `"abc"` → unique = {a,b,c} → count = 3
  - Palindromes: "aaa", "aba", "aca"
- Character `'b'`: first=1, last=1 → appears only once → skip
- Character `'c'`: first=3, last=3 → appears only once → skip

Total: 3 unique palindromes

### Time & Space Complexity:
- **Time**: O(n) - single pass to find boundaries + O(26×k) for substring operations ≈ O(n)
- **Space**: O(1) - fixed array for 26 characters + temporary sets for unique counting

# Tags

- String Manipulation
- Two Pointers
- Hash Set
- Palindrome
- Subsequence

