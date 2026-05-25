## Problem

https://leetcode.com/problems/palindrome-partitioning-iv/description

Given a string `s`, return `true` if it is possible to split the string `s` into **three non-empty palindromic substrings**. Otherwise, return `false`.

A string is said to be a palindrome if it reads the same forward and backward.

### Examples

**Example 1:**
```
Input: s = "abcbdd"
Output: true
Explanation: "abcbdd" = "a" + "bcb" + "dd", and all three substrings are palindromes.
```

**Example 2:**
```
Input: s = "bcbddxy"
Output: false
Explanation: s cannot be split into 3 palindromes.
```

### Constraints

- $3 \leq |s| \leq 2000$
- `s` consists only of lowercase English letters

## Observations

1. **Brute Force Approach**: We need to try all possible ways to split the string into 3 parts. With $O(n^2)$ possible splits, this would be expensive without preprocessing.

2. **Palindrome Preprocessing**: Instead of checking if a substring is a palindrome each time (which takes $O(n)$), we can **precompute all palindromes using dynamic programming**. Create a 2D table `dp[i][j]` where `dp[i][j] = true` if `s[i:j+1]` is a palindrome.

3. **Building the DP Table Efficiently**: We can build the palindrome table by:
   - Starting with single characters (always palindromes)
   - Expanding around centers:
     - **Odd-length palindromes**: expand from each single character center
     - **Even-length palindromes**: expand from each pair of adjacent equal characters

4. **Recursive Partitioning with Memoization**: Once we have the palindrome table, we use a recursive function `F(i, cnt)` that asks: "Can we partition `s[i:n]` into exactly `cnt` palindromes?"
   - Base case: if `cnt == 1`, check if `s[i:n]` is a palindrome
   - Recursive case: try all possible first palindromes `s[i:j]`, then recursively check if the rest can be partitioned
   - Memoize results to avoid recomputation

5. **Time Complexity**:
   - Building palindrome table: $O(n^2)$
   - Recursive search with memoization: $O(n^2)$ states × $O(n)$ per state = $O(n^3)$
   - Overall: $O(n^3)$

6. **Space Complexity**: $O(n^2)$ for the DP table + $O(n^2)$ for memoization cache

## Solution

```python
class Solution:
    def checkPartitioning(self, s: str) -> bool:
        n = len(s)
        
        # Step 1: Precompute all palindromes using dynamic programming
        dp = [[False] * n for _ in range(n)]
        
        # Single characters are always palindromes
        for i in range(n):
            dp[i][i] = True
            # Check two-character palindromes
            if i > 0 and s[i - 1] == s[i]:
                dp[i - 1][i] = True
        
        # Expand around odd-length centers (single character)
        for i in range(n):
            l, r = i - 1, i + 1
            while l >= 0 and r < n and s[l] == s[r]:
                dp[l][r] = True
                l -= 1
                r += 1
            
            # Expand around even-length centers (two adjacent characters)
            if i > 0 and dp[i - 1][i]:
                l, r = i - 2, i + 1
                while l >= 0 and r < n and s[l] == s[r]:
                    dp[l][r] = True
                    l -= 1
                    r += 1
        
        # Helper function to check if substring is palindrome
        def check_palin(l: int, r: int) -> bool:
            return dp[l][r]
        
        # Step 2: Use memoized recursion to partition into 3 palindromes
        mem = {}
        
        def F(i: int, cnt: int) -> bool:
            """
            Check if s[i:n] can be partitioned into exactly cnt palindromes.
            
            Args:
                i: Starting index in string s
                cnt: Number of palindromes needed
            
            Returns:
                True if partition is possible, False otherwise
            """
            # Base case: if we need exactly 1 palindrome, check if s[i:n] is palindrome
            if cnt == 1:
                return check_palin(i, n - 1)
            
            # Check memoization cache
            if (i, cnt) in mem:
                return mem[(i, cnt)]
            
            res = False
            # Try all possible positions for the first palindrome
            # j ranges from i+1 to n-cnt+2 to ensure we have room for remaining palindromes
            for j in range(i + 1, n - cnt + 2):
                # If s[i:j] is a palindrome AND s[j:n] can be split into (cnt-1) palindromes
                if check_palin(i, j - 1) and F(j, cnt - 1):
                    res = True
                    break
            
            mem[(i, cnt)] = res
            return res
        
        # Start from index 0, need to split into 3 palindromes
        return F(0, 3)
```

### Walkthrough Example: `s = "abcbdd"`

**Palindrome Table (dp):**
```
    a  b  c  b  d  d
a  [T  F  F  F  F  F]
b   [F  T  F  T  F  F]
c   [F  F  T  F  F  F]
b   [F  F  F  T  F  F]
d   [F  F  F  F  T  T]
d   [F  F  F  F  F  T]

dp[1][3] = True  (bcb is palindrome)
dp[4][5] = True  (dd is palindrome)
dp[0][0] = True  (a is palindrome)
```

**Recursive Search:**
- `F(0, 3)`: Split from index 0 into 3 palindromes
  - Try `j=1`: Is `s[0:1]` ("a") a palindrome? YES
    - `F(1, 2)`: Split from index 1 into 2 palindromes
      - Try `j=4`: Is `s[1:4]` ("bcb") a palindrome? YES
        - `F(4, 1)`: Is `s[4:6]` ("dd") a palindrome? YES ✓
        - Return `True`
      - Return `True`
    - Return `True`
  - Return `True`

Result: `True` ✓

## Tags

- Dynamic Programming
- String Manipulation
- Palindrome
- Recursion + Memoization
- Preprocessing

