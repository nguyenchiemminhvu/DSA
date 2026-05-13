## Problem

https://leetcode.com/problems/longest-valid-parentheses/description

Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses substring.

### Examples

**Example 1:**
- Input: `s = "(()"` 
- Output: `2`
- Explanation: The longest valid parentheses substring is `"()"`.

**Example 2:**
- Input: `s = ")()())"`
- Output: `4`
- Explanation: The longest valid parentheses substring is `"()()"`.

**Example 3:**
- Input: `s = ""`
- Output: `0`

### Constraints

- `0 <= s.length <= 3 * 10^4`
- `s[i]` is `'('` or `')'`

## Observations

1. **Structure of Valid Parentheses**: A valid parentheses substring must have:
   - Equal number of opening '(' and closing ')'
   - Every closing ')' must have a matching opening '(' before it
   - The string is continuous (substring, not subsequence)

2. **Key Insight - DP State**: We can define `dp[i]` as the length of the longest valid parentheses **ending at index i**. This is crucial because:
   - If `s[i] == '('`, then `dp[i] = 0` (valid parentheses must end with ')')
   - If `s[i] == ')'`, we need to check if we can extend a previous valid substring

3. **Two Cases When `s[i] == ')'`**:
   - **Case 1**: `s[i-1] == '('` → We have a pair `"()"` at positions `i-1` and `i`
     - `dp[i] = 2 + dp[i-2]` (add the pair to any valid substring before position `i-2`)
   
   - **Case 2**: `s[i-1] == ')'` → The previous position ends a valid substring
     - We know `dp[i-1]` tells us how long that valid substring is
     - We need to check the character **before** that substring: at index `i - dp[i-1] - 1`
     - If that character is `'('`, we can match it with current `')'`
     - `dp[i] = 2 + dp[i-1] + dp[i-dp[i-1]-2]`

4. **Answer**: The maximum value in the `dp` array (longest valid substring ending anywhere)

5. **Example Walkthrough** for `")()())"`:
   ```
   Index:  0  1  2  3  4  5
   Char:   )  (  )  (  )  )
   dp:     0  0  2  0  4  5
   
   i=0: s[0]=')', no match → dp[0]=0
   i=1: s[1]='(', not ')' → dp[1]=0
   i=2: s[2]=')', s[1]='(' → dp[2]=2+dp[0]=2 (substring "()")
   i=3: s[3]='(', not ')' → dp[3]=0
   i=4: s[4]=')', s[3]='(' → dp[4]=2+dp[2]=2+2=4 (substring "()()")
   i=5: s[5]=')', s[4]=')', dp[4]=4 → check s[5-4-1]=s[0]=')', no match → dp[5]=0
   
   Answer: max(dp) = 4
   ```

## Solution

### Approach: Dynamic Programming (Bottom-Up)

**Time Complexity**: O(n)  
**Space Complexity**: O(n)

```python
class Solution:
    def longestValidParentheses(self, s: str) -> int:
        n = len(s)
        dp = [0] * n  # dp[i] = length of longest valid parentheses ending at i
        res = 0
        
        for i in range(1, n):
            if s[i] == ')':
                # Case 1: Previous char is '(' → we have "()"
                if s[i - 1] == '(':
                    dp[i] = 2 + (dp[i - 2] if i - 2 >= 0 else 0)
                # Case 2: Previous char is ')' → check before the valid substring
                else:
                    prev = dp[i - 1]  # Length of valid substring ending at i-1
                    j = i - prev - 1  # Index to check (before that substring)
                    if j >= 0 and s[j] == '(':
                        # Can match s[j] with s[i], extend the substring
                        dp[i] = 2 + prev + (dp[j - 1] if j - 1 >= 0 else 0)
            res = max(res, dp[i])
        
        return res
```

### Alternative: Top-Down DP (Memoization)

The commented-out code in the original solution uses memoization:
- `F(i)` returns the length of longest valid parentheses **ending at index i**
- For each position, we compute the same logic but in a recursive manner
- Memoization prevents recomputation of the same subproblems

### Why Bottom-Up DP is Better Here

1. **Iterative approach** is more straightforward and avoids recursion overhead
2. **Natural order**: We build up the solution from left to right
3. **Space-efficient**: We only maintain one 1D array

### Key Points to Remember

- **DP[i] represents**: Length of longest valid parentheses **ending at position i**
- **Initialization**: Start from index 1 (no valid parentheses can start with ')')
- **Only ')' matters**: We only update DP when we see a closing parenthesis
- **Two sub-cases**: Either matching "()" or extending previous valid substring

# Tags
- Dynamic Programming
- String Parsing
- Parentheses Matching

