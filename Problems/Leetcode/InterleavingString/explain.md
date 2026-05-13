## Problem

https://leetcode.com/problems/interleaving-string/description

Given strings `s1`, `s2`, and `s3`, determine whether `s3` is formed by an interleaving of `s1` and `s2`.

An **interleaving** of two strings `s` and `t` is a configuration where `s` and `t` are divided into `n` and `m` substrings respectively, such that:
- `s = s1 + s2 + ... + sn`
- `t = t1 + t2 + ... + tm`
- `|n - m| <= 1`

The interleaving is `s1 + t1 + s2 + t2 + s3 + t3 + ...` or `t1 + s1 + t2 + s2 + t3 + s3 + ...`

**Example 1:**
```
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true
Explanation: Split s1 = "aa" + "bc" + "c" and s2 = "dbbc" + "a"
Interleaving: "aa" + "dbbc" + "bc" + "a" + "c" = "aadbbcbcac"
```

**Example 2:**
```
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
```

**Example 3:**
```
Input: s1 = "", s2 = "", s3 = ""
Output: true
```

**Constraints:**
- `0 <= s1.length, s2.length <= 100`
- `0 <= s3.length <= 200`
- `s1`, `s2`, and `s3` consist of lowercase English letters

**Follow-up:** Could you solve it using only `O(s2.length)` additional memory space?

## Observations

1. **Length Check:** If `len(s1) + len(s2) != len(s3)`, it's impossible to form `s3` by interleaving, return `False` immediately.

2. **State Space:** At any position in `s3`, we need to track how many characters we've used from `s1` and `s2`. This forms a 2D state space `(i1, i2)` where:
   - `i1` = current index in `s1` (number of characters consumed)
   - `i2` = current index in `s2` (number of characters consumed)
   - Current character in `s3` should be at index `i1 + i2`

3. **Recursive Decision:** At each state `(i1, i2)`:
   - If `s1[i1] == s3[i1 + i2]`, we can choose to consume from `s1` → recurse to `(i1+1, i2)`
   - If `s2[i2] == s3[i1 + i2]`, we can choose to consume from `s2` → recurse to `(i1, i2+1)`
   - If either path leads to a valid interleaving, return `True`

4. **Base Cases:**
   - If `i1 == len(s1)`, check if remaining characters of `s2` match remaining `s3`
   - If `i2 == len(s2)`, check if remaining characters of `s1` match remaining `s3`

5. **Overlapping Subproblems:** The same state `(i1, i2)` can be reached through multiple paths, making this suitable for memoization (top-down DP) or tabulation (bottom-up DP).

6. **DP Table Filling Order:** Build the DP table bottom-up starting from the boundaries:
   - First, fill the last row (`i1 = len(s1)`)
   - Then, fill the last column (`i2 = len(s2)`)
   - Finally, fill remaining cells from bottom-right to top-left

## Solution

### Approach 1: Memoization (Top-Down DP)
```python
def isInterleave(self, s1: str, s2: str, t: str) -> bool:
    n1, n2, nt = len(s1), len(s2), len(t)
    if n1 + n2 != nt:
        return False
    
    mem = {}
    
    def F(i1: int, i2: int) -> bool:
        # Base cases: when we've consumed all of s1 or s2
        if i1 >= n1:
            return s2[i2:] == t[n1 + i2:]
        if i2 >= n2:
            return s1[i1:] == t[n2 + i1:]
        
        # Check memo
        if (i1, i2) in mem:
            return mem[(i1, i2)]
        
        # Try consuming from s1
        res = False
        if s1[i1] == t[i1 + i2]:
            res = res or F(i1 + 1, i2)
        
        # Try consuming from s2
        if s2[i2] == t[i1 + i2]:
            res = res or F(i1, i2 + 1)
        
        # Memoize and return
        mem[(i1, i2)] = res
        return res
    
    return F(0, 0)
```

**Time Complexity:** $O(n_1 \times n_2)$ - Each state `(i1, i2)` is computed once  
**Space Complexity:** $O(n_1 \times n_2)$ - Recursion stack and memoization table

### Approach 2: Tabulation (Bottom-Up DP) - **Optimal**
```python
def isInterleave(self, s1: str, s2: str, t: str) -> bool:
    n1, n2, nt = len(s1), len(s2), len(t)
    if n1 + n2 != nt:
        return False
    
    # dp[i1][i2] = True if we can form t[0:i1+i2] using s1[0:i1] and s2[0:i2]
    dp = [[False for _ in range(n2 + 1)] for _ in range(n1 + 1)]
    
    # Fill the last row: when all of s1 is consumed
    for i2 in range(n2 + 1):
        dp[n1][i2] = (s2[i2:] == t[n1 + i2:])
    
    # Fill the last column: when all of s2 is consumed
    for i1 in range(n1 + 1):
        dp[i1][n2] = (s1[i1:] == t[n2 + i1:])
    
    # Fill remaining cells bottom-up from right to left
    for i1 in range(n1 - 1, -1, -1):
        for i2 in range(n2 - 1, -1, -1):
            op1, op2 = False, False
            
            # Can we consume from s1?
            if s1[i1] == t[i1 + i2]:
                op1 = dp[i1 + 1][i2]
            
            # Can we consume from s2?
            if s2[i2] == t[i1 + i2]:
                op2 = dp[i1][i2 + 1]
            
            # Either option works
            dp[i1][i2] = op1 or op2
    
    return dp[0][0]
```

**Time Complexity:** $O(n_1 \times n_2)$  
**Space Complexity:** $O(n_1 \times n_2)$

### Approach 3: Space-Optimized DP (Follow-up Solution)
Since we only need the next row to compute the current row, we can use a 1D array instead of a 2D array.

```python
def isInterleave(self, s1: str, s2: str, t: str) -> bool:
    n1, n2, nt = len(s1), len(s2), len(t)
    if n1 + n2 != nt:
        return False
    
    # Use 1D DP array: dp[i2] represents the state for current i1
    dp = [False] * (n2 + 1)
    
    # Base case: empty strings interleave to empty string
    dp[n2] = True
    
    # Initialize last row
    for i2 in range(n2 - 1, -1, -1):
        dp[i2] = (s2[i2:] == t[n1 + i2:])
    
    # Process each row from bottom to top
    for i1 in range(n1 - 1, -1, -1):
        # Start of this row
        dp[n2] = (s1[i1:] == t[n2 + i1:])
        
        # Fill from right to left
        for i2 in range(n2 - 1, -1, -1):
            op1 = op2 = False
            
            if s1[i1] == t[i1 + i2]:
                op1 = dp[i2]  # From below (i1+1, i2)
            
            if s2[i2] == t[i1 + i2]:
                op2 = dp[i2 + 1]  # From right (i1, i2+1)
            
            dp[i2] = op1 or op2
    
    return dp[0]
```

**Time Complexity:** $O(n_1 \times n_2)$  
**Space Complexity:** $O(n_2)$ - **Answer to follow-up question!**

### Example Walkthrough

For `s1 = "aabcc"`, `s2 = "dbbca"`, `s3 = "aadbbcbcac"`:

DP table construction (bottom-up):
```
       i2: 0     1     2     3     4     5(n2)
i1: 0     T     T     T     T     F     F
    1     T     T     T     F     F     F
    2     T     T     F     F     F     F
    3     T     F     F     F     F     F
    4     F     F     F     F     F     F
    5(n1) F     F     F     F     F     T
```

At `dp[0][0]`: Can we form "aadbbcbcac" from s1="aabcc" and s2="dbbca"?
- Following one valid path: consume "aa" from s1, "dbbc" from s2, "bc" from s1, "a" from s2, "c" from s1
- Result: `True`

# Tags

- Dynamic Programming
- String Matching
- 2D DP / Tabulation
- Space Optimization
- Interleaving

