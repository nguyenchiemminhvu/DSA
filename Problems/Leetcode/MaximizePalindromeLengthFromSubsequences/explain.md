## Problem

https://leetcode.com/problems/maximize-palindrome-length-from-subsequences/description

Given two strings `word1` and `word2`, construct a palindrome by:
1. Choosing a non-empty subsequence from `word1`
2. Choosing a non-empty subsequence from `word2`
3. Concatenating them: `subsequence1 + subsequence2`

Return the length of the longest palindrome that can be constructed. If no palindrome can be formed, return 0.

**Examples:**
- `word1 = "cacb"`, `word2 = "cbba"` → Output: 5 (choose "ab" + "cba" = "abcba")
- `word1 = "ab"`, `word2 = "ab"` → Output: 3 (choose "ab" + "a" = "aba")
- `word1 = "aa"`, `word2 = "bb"` → Output: 0 (no palindrome possible)

**Constraints:**
- 1 ≤ word1.length, word2.length ≤ 1000
- Both strings consist of lowercase English letters

## Observations

1. **Key Insight**: We need to find two subsequences from different strings that when concatenated form a palindrome. For a concatenation to be a palindrome, characters must be "mirrored" across the boundary.

2. **Palindrome Property**: For `s1 + s2` to form a palindrome:
   - If we match characters from positions `l` and `r` in the concatenated string, they must be equal
   - The critical constraint: at least one character must come from `word1` (left) and at least one from `word2` (right)
   - We need `l < len(word1)` and `r >= len(word1)` at the point where we establish the palindrome

3. **Strategy**: 
   - Concatenate both strings: `s = word1 + word2`
   - Use dynamic programming to find the longest palindromic subsequence
   - Only count palindromes that span across the boundary (have characters from both strings)

4. **DP State**: `dp[l][r]` = length of the longest palindromic subsequence in `s[l:r+1]`

5. **Transitions**:
   - If `s[l] == s[r]`: We can extend the palindrome by 2: `dp[l][r] = 2 + dp[l+1][r-1]`
   - If `s[l] != s[r]`: We try excluding either end: `dp[l][r] = max(dp[l+1][r], dp[l][r-1])`

6. **Valid Palindrome**: Only count if:
   - `l < len(word1)` (left character from word1)
   - `r >= len(word1)` (right character from word2)
   - This ensures we have characters from both strings

## Solution

### Approach: Dynamic Programming with Boundary Constraint

The solution uses a 2D DP table where `dp[l][r]` represents the length of the longest palindromic subsequence from index `l` to `r` in the concatenated string.

**Key Algorithm Steps:**

1. **Initialization**: 
   - Single characters are palindromes of length 1: `dp[i][i] = 1`

2. **Fill DP Table**:
   - Iterate from longer subsequences to shorter ones
   - For each pair `(l, r)`:
     - If `s[l] == s[r]`: Can form palindrome by including both ends + middle palindrome
     - If `s[l] != s[r]`: Take the better option of excluding left or right end

3. **Track Valid Palindromes**:
   - Only update `max_pal` when the palindrome spans the boundary: `l < n1 and r >= n1`
   - This guarantees at least one character from each string

**Time Complexity**: O(n²) where n = len(word1) + len(word2)
- Fill all O(n²) cells
- Each cell takes O(1) to compute

**Space Complexity**: O(n²) for the DP table

### Code Explanation

```python
class Solution:
    def longestPalindrome(self, s1: str, s2: str) -> int:
        s = s1 + s2
        n = len(s)
        n1, n2 = len(s1), len(s2)
        max_pal = 0

        # DP table: dp[l][r] = longest palindromic subsequence length from s[l] to s[r]
        dp = [[0] * n for _ in range(n)]
        
        # Base case: single characters are palindromes
        for i in range(n):
            dp[i][i] = 1
        
        # Fill DP table from longer to shorter subsequences
        for l in range(n - 1, -1, -1):
            for r in range(l + 1, n):
                # If outer characters match, they can be part of the palindrome
                if s[l] == s[r]:
                    dp[l][r] = max(dp[l][r], 2 + dp[l + 1][r - 1])
                    
                    # Valid palindrome: must span both strings
                    # l < n1: left character from word1
                    # r >= n1: right character from word2
                    if l < n1 and r >= n1:
                        max_pal = max(max_pal, dp[l][r])
                else:
                    # If they don't match, try excluding either end
                    dp[l][r] = max(dp[l][r], dp[l + 1][r], dp[l][r - 1])

        return max_pal
```

### Alternative: Memoization Approach (Commented Out)

The commented recursive solution uses top-down memoization:
- `F(l, r)` returns the length of longest palindromic subsequence in range `[l, r]`
- Checks the boundary condition `l < n1 and r >= n1` whenever characters match
- More intuitive but slightly higher overhead due to function calls

### Example Walkthrough

**Example 1:** `word1 = "cacb"`, `word2 = "cbba"`

String: `"cacbcbba"` (indices 0-7, split at index 4)

When we find the palindrome "abcba":
- Characters from word1: "ab" at indices 1, 2
- Characters from word2: "cba" at indices 4, 5, 6
- The matching happens between index 2 ('b' from word1) and index 6 ('b' from word2)
- This spans the boundary (2 < 4 and 6 >= 4), so it's valid

The DP correctly identifies this and returns 5.

# Tags
- Dynamic Programming
- Palindrome
- Subsequence
- String Matching
- Two Pointers

