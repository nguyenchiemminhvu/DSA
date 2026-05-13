## Problem

https://leetcode.com/problems/longest-palindromic-subsequence/description

Given a string `s`, find the length of the **longest palindromic subsequence** in `s`.

A **subsequence** is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.

### Examples

**Example 1:**
- Input: `s = "bbbab"`
- Output: `4`
- Explanation: One possible longest palindromic subsequence is `"bbbb"`

**Example 2:**
- Input: `s = "cbbd"`
- Output: `2`
- Explanation: One possible longest palindromic subsequence is `"bb"`

### Constraints

- `1 <= s.length <= 1000`
- `s` consists only of lowercase English letters

## Observations

1. **Palindrome Property**: A palindrome reads the same forwards and backwards (e.g., "aba", "racecar")

2. **Subsequence vs Substring**: We're looking for a subsequence, not substring, which means we can skip characters but must maintain their relative order

3. **Key Insight - Range Dependency**: The problem exhibits optimal substructure. For a substring from index `l` to `r`:
   - If `s[l] == s[r]`, the longest palindromic subsequence includes both characters plus the longest palindromic subsequence of `s[l+1...r-1]`
   - If `s[l] != s[r]`, the longest palindromic subsequence is the maximum of:
     - Longest palindromic subsequence in `s[l+1...r]`
     - Longest palindromic subsequence in `s[l...r-1]`

4. **Recursive Structure**: This naturally leads to a recursive solution with overlapping subproblems, suitable for memoization or dynamic programming

5. **Complexity Trade-off**: 
   - Memoization uses O(n²) space for the memo table
   - Tabulation uses O(n²) space for the DP table and is typically faster due to less overhead

## Solution

### Approach 1: Memoization (Top-Down)

```python
def longestPalindromeSubseq(self, s: str) -> int:
    n = len(s)
    mem = {}
    
    def F(l: int, r: int) -> int:
        # Base cases
        if l > r:
            return 0
        if l == r:
            return 1
        
        # Check memo
        if (l, r) in mem:
            return mem[(l, r)]
        
        # Recursive case
        if s[l] == s[r]:
            res = 2 + F(l + 1, r - 1)
        else:
            res = max(F(l + 1, r), F(l, r - 1))
        
        mem[(l, r)] = res
        return res
    
    return F(0, n - 1)
```

**Time Complexity**: O(n²) - we compute each subproblem at most once, and there are O(n²) subproblems

**Space Complexity**: O(n²) - memo table stores O(n²) entries, plus O(n) recursion stack depth

### Approach 2: Tabulation (Bottom-Up) - Preferred

```python
def longestPalindromeSubseq(self, s: str) -> int:
    n = len(s)
    dp = [[0 for _ in range(n)] for _ in range(n)]
    
    # Fill the DP table
    # Process from left to right (l from n-1 to 0)
    for l in range(n - 1, -1, -1):
        for r in range(n):
            if l > r:
                dp[l][r] = 0
            elif l == r:
                dp[l][r] = 1
            else:
                if s[l] == s[r]:
                    dp[l][r] = 2 + dp[l + 1][r - 1]
                else:
                    dp[l][r] = max(dp[l + 1][r], dp[l][r - 1])
    
    return dp[0][n - 1]
```

**Time Complexity**: O(n²) - we fill n² cells, each taking O(1) time

**Space Complexity**: O(n²) - DP table of size n × n

### Key Differences Between Approaches

| Aspect | Memoization | Tabulation |
|--------|-------------|-----------|
| Direction | Top-down (from problem to subproblems) | Bottom-up (from base cases to solution) |
| Function calls | Multiple recursive calls with memoization | Iterative computation |
| Speed | Slightly slower due to function call overhead | Faster, more cache-friendly |
| When to use | When the subproblem space is sparse | When most/all subproblems are needed |

### Example Walkthrough

For `s = "bbbab"`:

```
    0   1   2   3   4
    b   b   b   a   b
0 b 1   2   3   3   4
1 b     1   2   2   3
2 b         1   1   3
3 a             1   1
4 b                 1
```

- `dp[0][4]` (entire string): Characters 'b' and 'b' match → 2 + `dp[1][3]` = 2 + 2 = 4
- `dp[1][3]` (substring "bbab"): Characters 'b' and 'a' don't match → max(`dp[2][3]`, `dp[1][2]`) = max(1, 2) = 2
- `dp[2][2]` (single char 'b'): 1
- `dp[1][2]` (substring "bb"): Characters match → 2 + `dp[2][1]` = 2 + 0 = 2

**Answer**: 4 (the palindrome "bbbb")

# Tags

- Dynamic Programming
- String
- Subsequence
- Palindrome
- Memoization
- Tabulation

