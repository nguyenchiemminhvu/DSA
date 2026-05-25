## Problem

https://leetcode.com/problems/shortest-common-supersequence/description

Given two strings `str1` and `str2`, return the shortest string that has both `str1` and `str2` as subsequences. If there are multiple valid strings, return any of them.

A string `s` is a subsequence of string `t` if deleting some number of characters from `t` (possibly 0) results in the string `s`.

### Examples

**Example 1:**
- Input: `str1 = "abac"`, `str2 = "cab"`
- Output: `"cabac"`
- Explanation: 
  - `str1 = "abac"` is a subsequence of `"cabac"` (delete first 'c')
  - `str2 = "cab"` is a subsequence of `"cabac"` (delete last 'ac')

**Example 2:**
- Input: `str1 = "aaaaaaaa"`, `str2 = "aaaaaaaa"`
- Output: `"aaaaaaaa"`

### Constraints

- $1 \leq \text{str1.length, str2.length} \leq 1000$
- `str1` and `str2` consist of lowercase English letters

## Observations

1. **Connection to LCS (Longest Common Subsequence):**
   - The shortest common supersequence length = `len(str1) + len(str2) - LCS_length`
   - We need to find the LCS first to build the shortest supersequence efficiently

2. **DP Table Represents LCS:**
   - `dp[i][j]` represents the length of the longest common subsequence of `str1[0...i-1]` and `str2[0...j-1]`
   - When characters match: `dp[i][j] = 1 + dp[i-1][j-1]`
   - When they don't match: `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`

3. **Backtracking Strategy:**
   - Start from `dp[n1][n2]` (bottom-right corner)
   - If characters match, include that character once (it's part of both strings)
   - If they don't match, we follow the direction with the larger value:
     - If `dp[i-1][j] > dp[i][j-1]`, include character from `str1`
     - Otherwise, include character from `str2`
   - When one string is exhausted, append remaining characters from the other

4. **Why This Greedy Backtracking Works:**
   - The DP table encodes which subsequences are actually used in the LCS
   - By following the path with higher DP values, we're following the LCS alignment
   - Non-matching characters are only included once (from whichever string we choose)
   - This ensures both strings remain subsequences of the result

## Solution

```python
class Solution:
    def shortestCommonSupersequence(self, s1: str, s2: str) -> str:
        n1, n2 = len(s1), len(s2)

        # Step 1: Build DP table for LCS
        dp = [[0 for _ in range(n2 + 1)] for _ in range(n1 + 1)]
        for i1 in range(1, n1 + 1):
            c1 = s1[i1 - 1]
            for i2 in range(1, n2 + 1):
                c2 = s2[i2 - 1]
                if c1 == c2:
                    # Characters match: extend LCS
                    dp[i1][i2] = 1 + dp[i1 - 1][i2 - 1]
                else:
                    # Characters don't match: take max from left or top
                    dp[i1][i2] = max(dp[i1 - 1][i2], dp[i1][i2 - 1])
        
        # Step 2: Backtrack to build the result
        res = []
        i1, i2 = n1, n2
        
        # Traverse from bottom-right to top-left
        while i1 > 0 and i2 > 0:
            if s1[i1 - 1] == s2[i2 - 1]:
                # Characters match: include once (part of LCS)
                res.append(s1[i1 - 1])
                i1 -= 1
                i2 -= 1
            else:
                # Characters don't match: follow the direction with larger DP value
                if dp[i1 - 1][i2] > dp[i1][i2 - 1]:
                    # Include from s1
                    res.append(s1[i1 - 1])
                    i1 -= 1
                else:
                    # Include from s2
                    res.append(s2[i2 - 1])
                    i2 -= 1
        
        # Append remaining characters from s1
        while i1 > 0:
            res.append(s1[i1 - 1])
            i1 -= 1
        
        # Append remaining characters from s2
        while i2 > 0:
            res.append(s2[i2 - 1])
            i2 -= 1

        # Reverse since we built the result backwards
        res.reverse()
        return "".join(res)
```

### Complexity Analysis

- **Time Complexity:** $O(n_1 \times n_2)$ where $n_1 = \text{len(s1)}$ and $n_2 = \text{len(s2)}$
  - DP table construction: $O(n_1 \times n_2)$
  - Backtracking: $O(n_1 + n_2)$
  
- **Space Complexity:** $O(n_1 \times n_2)$ for the DP table

### Walkthrough Example

For `s1 = "abac"` and `s2 = "cab"`:

**DP Table:**
```
      ""  c  a  b
  ""   0  0  0  0
  a    0  0  1  1
  b    0  0  1  2
  a    0  1  1  2
  c    0  1  1  2
```

**Backtracking (from dp[4][3]):**
1. `s1[3]='c'` vs `s2[2]='b'`: mismatch, `dp[3][3]=2 > dp[4][2]=1`, take from s1 → 'c'
2. `s1[2]='a'` vs `s2[2]='b'`: mismatch, `dp[2][3]=2 > dp[3][2]=1`, take from s1 → 'a'
3. `s1[1]='b'` vs `s2[2]='b'`: match → 'b'
4. `s1[0]='a'` vs `s2[1]='a'`: match → 'a'
5. `s1[-1]` vs `s2[0]='c'`: take from s2 → 'c'

Result (reversed): `"cabac"` ✓

# Tags
- Longest Common Subsequence
- Dynamic Programming
- String Manipulation
- Backtracking

