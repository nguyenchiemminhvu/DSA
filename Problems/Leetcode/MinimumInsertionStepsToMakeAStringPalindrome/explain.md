## Problem

https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/description/

Given a string `s`, in one step you can insert any character at any index of the string.

**Return the minimum number of steps to make `s` a palindrome.**

A Palindrome String is one that reads the same backward as well as forward.

### Examples

**Example 1:**
- Input: `s = "zzazz"`
- Output: `0`
- Explanation: The string "zzazz" is already a palindrome, we do not need any insertions.

**Example 2:**
- Input: `s = "mbadm"`
- Output: `2`
- Explanation: String can become "mbdadbm" or "mdbabdm".

**Example 3:**
- Input: `s = "leetcode"`
- Output: `5`
- Explanation: Inserting 5 characters the string becomes "leetcodocteel".

### Constraints

- `1 <= s.length <= 500`
- `s` consists of lowercase English letters.

## Observations

1. **Core Insight**: To make a string a palindrome with minimum insertions, we need to find the longest palindromic subsequence (LPS) already present in the string. The minimum insertions required = `length of string - length of LPS`.

2. **Why LPS?**: If we have a palindromic subsequence, all characters in it are already in the correct relative positions. We only need to insert characters to fill the gaps.

3. **DP Subproblem**: Define `dp[l][r]` = minimum insertions needed to make substring `s[l:r+1]` a palindrome.

4. **Recurrence Relation**:
   - If `s[l] == s[r]`: Characters at both ends match, so `dp[l][r] = dp[l+1][r-1]`
   - If `s[l] != s[r]`: We need to insert one character. Either:
     - Insert at the right to match `s[l]`: `dp[l][r] = 1 + dp[l+1][r]` (skip left pointer)
     - Insert at the left to match `s[r]`: `dp[l][r] = 1 + dp[l][r-1]` (skip right pointer)
     - Take the minimum of both options

5. **Base Case**: When `l >= r`, the substring is already a palindrome (empty or single character), so `dp[l][r] = 0`.

6. **Fill Order**: Process from right to left for `l`, and from left to right for `r`, ensuring dependencies are resolved before use.

## Solution

### Approach 1: Recursive with Memoization (Top-Down DP)

```python
class Solution:
    def minInsertions(self, s: str) -> int:
        n = len(s)
        mem = {}
        
        def F(l: int, r: int) -> int:
            # Base case: substring is already a palindrome
            if l >= r:
                return 0
            
            # Check memoization
            if (l, r) in mem:
                return mem[(l, r)]
            
            min_steps = float('inf')
            
            if s[l] == s[r]:
                # Characters match, move both pointers inward
                min_steps = min(min_steps, F(l + 1, r - 1))
            else:
                # Characters don't match, try both insertions
                # Insert right of l or left of r
                min_steps = min(min_steps, 1 + min(F(l + 1, r), F(l, r - 1)))
            
            mem[(l, r)] = min_steps
            return min_steps
        
        return F(0, n - 1)
```

**Time Complexity**: $O(n^2)$ - At most $n^2$ unique subproblems  
**Space Complexity**: $O(n^2)$ - Memoization table + recursion stack

### Approach 2: Iterative DP (Bottom-Up) ⭐ Recommended

```python
class Solution:
    def minInsertions(self, s: str) -> int:
        n = len(s)
        
        # dp[l][r] = minimum insertions to make s[l:r+1] a palindrome
        dp = [[float('inf') for _ in range(n)] for _ in range(n)]
        
        # Base case: single characters and empty ranges are palindromes
        for i in range(n):
            dp[i][i] = 0
        
        # Fill diagonals from shorter to longer substrings
        for length in range(2, n + 1):  # substring length
            for l in range(n - length + 1):
                r = l + length - 1
                if s[l] == s[r]:
                    # Characters match
                    if l + 1 <= r - 1:
                        dp[l][r] = dp[l + 1][r - 1]
                    else:
                        dp[l][r] = 0  # Adjacent or same character
                else:
                    # Characters don't match, need insertion
                    dp[l][r] = 1 + min(dp[l + 1][r], dp[l][r - 1])
        
        return dp[0][n - 1]
```

**Time Complexity**: $O(n^2)$ - Two nested loops covering all substrings  
**Space Complexity**: $O(n^2)$ - DP table

### How It Works (Example: "mbadm")

```
String: m b a d m
Index:  0 1 2 3 4

DP table (minimum insertions needed):
       0   1   2   3   4
    0  0   1   2   2   2
    1      0   1   2   3
    2          0   1   2
    3              0   1
    4                  0

Processing:
- dp[0][0] = 0 (single char 'm')
- dp[0][1]: 'm' != 'b' → 1 + min(dp[1][1], dp[0][0]) = 1
- dp[0][4]: 'm' == 'm' → dp[1][3] = 2
```

For "mbadm":
- Need to insert 2 characters
- Can become "mbdadbm" or "mdbabdm"

## Tags

- Dynamic Programming
- String
- Longest Palindromic Subsequence (LPS)
- Interval DP

