## Problem

https://leetcode.com/problems/distinct-subsequences/description

Given two strings `s` and `t`, return the number of **distinct subsequences** of `s` which equals `t`.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

**Constraints:**
- 1 <= s.length, t.length <= 1000
- s and t consist of English letters
- The answer fits on a 32-bit signed integer

**Examples:**

Example 1:
```
Input: s = "rabbbit", t = "rabbit"
Output: 3
Explanation:
rabbbit
rabbbit
rabbbit
```

Example 2:
```
Input: s = "babgbag", t = "bag"
Output: 5
Explanation:
babgbag
babgbag
babgbag
babgbag
babgbag
```

## Observations

1. **This is a dynamic programming problem**: We need to count the number of ways to form string `t` from string `s` by selecting characters from `s` while maintaining their relative order.

2. **Recursive structure**: For each character in `s`, we have two choices:
   - Skip the current character in `s`
   - If it matches the current character in `t`, we can either take it (and move both pointers forward) or skip it

3. **Overlapping subproblems**: The same state (current position in `s`, current position in `t`) can be reached multiple times, making memoization or tabulation efficient.

4. **Base cases**:
   - If we've consumed all of `t` (matched all characters), there's exactly 1 way (return 1)
   - If we've consumed all of `s` but not all of `t`, there's no way (return 0)

5. **Pattern**: This is a classic **"edit distance" style** problem but instead of minimum operations, we count distinct ways.

## Solution

### Approach 1: Top-Down Dynamic Programming (Memoization)

The recursive approach with memoization:

```python
def numDistinct(self, s: str, t: str) -> int:
    ns, nt = len(s), len(t)
    mem = {}
    
    def F(i: int, it: int) -> int:
        # Base case: matched all characters in t
        if it >= nt:
            return 1
        # Base case: no more characters in s but t not fully matched
        if i >= ns:
            return 0
        # Return memoized result if available
        if (i, it) in mem:
            return mem[(i, it)]
        
        count = 0
        # Option 1: If current characters match, we can take this character
        if s[i] == t[it]:
            count += F(i + 1, it + 1)  # Take current character from s
        
        # Option 2: Always skip current character in s
        count += F(i + 1, it)
        
        mem[(i, it)] = count
        return count
    
    return F(0, 0)
```

**Time Complexity**: O(ns × nt) - we compute each state once  
**Space Complexity**: O(ns × nt) - memoization table + recursion stack

### Approach 2: Bottom-Up Dynamic Programming (Tabulation) - Optimal

The iterative approach builds the solution from the bottom up:

```python
def numDistinct(self, s: str, t: str) -> int:
    ns, nt = len(s), len(t)
    
    # dp[i][j] = number of distinct subsequences of s[0:i] that equal t[0:j]
    dp = [[0 for _ in range(nt + 1)] for _ in range(ns + 1)]
    
    # Base case: empty t can always be formed in exactly 1 way (select nothing)
    for i in range(ns + 1):
        dp[i][nt] = 1
    
    # Fill the table backwards
    for i in range(ns - 1, -1, -1):
        for it in range(nt - 1, -1, -1):
            # Option 1: Skip current character in s
            dp[i][it] = dp[i + 1][it]
            
            # Option 2: If characters match, we can take it
            if s[i] == t[it]:
                dp[i][it] += dp[i + 1][it + 1]
    
    return dp[0][0]
```

**Time Complexity**: O(ns × nt)  
**Space Complexity**: O(ns × nt)

### Why This Works - Detailed Example

For `s = "rabbbit"` and `t = "rabbit"`:

The DP table at key positions:

```
       ""  r  a  b  b  i  t
    "" 1   0  0  0  0  0  0
    r  1   1  0  0  0  0  0
    a  1   1  1  0  0  0  0
    b  1   1  1  1  0  0  0
    b  1   1  1  2  1  0  0
    b  1   1  1  3  3  0  0
    i  1   1  1  3  3  3  0
    t  1   1  1  3  3  3  3
```

The three ways to form "rabbit" are:
1. r(0) + a(1) + b(2) + b(3) + i(4) + t(6)
2. r(0) + a(1) + b(2) + b(4) + i(5) + t(6)
3. r(0) + a(1) + b(3) + b(4) + i(5) + t(6)

# Tags

#dynamic-programming #string-subsequence #two-pointers #memoization #tabulation

