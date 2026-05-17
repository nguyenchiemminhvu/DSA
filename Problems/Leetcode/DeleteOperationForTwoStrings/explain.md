## Problem

https://leetcode.com/problems/delete-operation-for-two-strings/description

Given two strings `word1` and `word2`, return the minimum number of steps required to make `word1` and `word2` the same. In one step, you can delete exactly one character in either string.

**Example 1:**
- Input: `word1 = "sea"`, `word2 = "eat"`
- Output: `2`
- Explanation: Delete 'e' from "sea" → "sa", delete 'a' from "eat" → "et", or delete 's' from "sea" → "ea" and delete 't' from "eat" → "ea"

**Example 2:**
- Input: `word1 = "leetcode"`, `word2 = "etco"`
- Output: `4`

**Constraints:**
- 1 ≤ word1.length, word2.length ≤ 500
- word1 and word2 consist of only lowercase English letters

---

## Observations

1. **Complement to Longest Common Subsequence (LCS)**
   - The problem is equivalent to finding the maximum length of a common subsequence
   - If LCS has length L, then we need to delete (len(word1) - L) + (len(word2) - L) characters
   - Formula: `minDistance = len(word1) + len(word2) - 2 * LCS_length`

2. **Optimal Substructure**
   - When characters match: we don't need to delete them, so we move both pointers
   - When characters don't match: we must delete one character, so we explore both options (delete from word1 or delete from word2)
   - The minimum deletions for a subproblem depends only on smaller subproblems

3. **Overlapping Subproblems**
   - The same subproblems are computed multiple times when using naive recursion
   - This makes dynamic programming an efficient approach

---

## Solution

### Approach: Bottom-Up Dynamic Programming

**State Definition:** `dp[i1][i2]` = minimum number of deletions to make `s1[i1..n1-1]` and `s2[i2..n2-1]` equal

**Base Cases:**
- `dp[n1][n2] = 0`: Both strings exhausted, no deletions needed
- `dp[i1][n2] = n1 - i1`: Delete all remaining characters from s1
- `dp[n1][i2] = n2 - i2`: Delete all remaining characters from s2

**Recurrence:**
```
If s1[i1] == s2[i2]:
    dp[i1][i2] = dp[i1+1][i2+1]          # Characters match, keep both
Else:
    dp[i1][i2] = 1 + min(
        dp[i1+1][i2],                     # Delete from s1
        dp[i1][i2+1]                      # Delete from s2
    )
```

**Why it works:** When characters match, they can be part of the final common string. When they don't, we must delete at least one and pick the option that minimizes total deletions.

### Time & Space Complexity
- **Time:** O(n₁ × n₂) - fill entire DP table
- **Space:** O(n₁ × n₂) - store 2D table

### Memoization (Top-Down)

```python
def minDistance(self, s1: str, s2: str) -> int:
    n1, n2 = len(s1), len(s2)
    mem = {}
    
    def F(i1: int, i2: int) -> int:
        if i1 < 0:
            return i2 + 1
        if i2 < 0:
            return i1 + 1
        if (i1, i2) in mem:
            return mem[(i1, i2)]
        
        res = float('inf')
        if s1[i1] == s2[i2]:
            res = min(res, F(i1 - 1, i2 - 1))
        else:
            res = min(
                res,
                1 + F(i1 - 1, i2),
                1 + F(i1, i2 - 1)
            )
        
        mem[(i1, i2)] = res
        return res
    
    return F(n1 - 1, n2 - 1)
```

### Tabulation (Bottom-Up) - Recommended

```python
def minDistance(self, s1: str, s2: str) -> int:
    n1, n2 = len(s1), len(s2)
    
    # dp[i1][i2] = min deletions for s1[i1:] and s2[i2:]
    dp = [[float('inf')] * (n2 + 1) for _ in range(n1 + 1)]
    
    # Base cases
    dp[n1][n2] = 0
    for i1 in range(n1):
        dp[i1][n2] = n1 - i1
    for i2 in range(n2):
        dp[n1][i2] = n2 - i2
    
    # Fill table from bottom-right to top-left
    for i1 in range(n1 - 1, -1, -1):
        for i2 in range(n2 - 1, -1, -1):
            if s1[i1] == s2[i2]:
                dp[i1][i2] = min(dp[i1][i2], dp[i1 + 1][i2 + 1])
            else:
                dp[i1][i2] = min(
                    dp[i1][i2],
                    1 + dp[i1 + 1][i2],
                    1 + dp[i1][i2 + 1]
                )
    
    return dp[0][0]
```

### Example Trace: "sea" vs "eat"

DP table (rows = characters from "sea", columns = characters from "eat"):

```
           ""  e  a  t
       ""   0  1  2  3
       s    1  1  2  3
       e    2  1  2  3
       a    3  2  1  2
```

Working backwards:
- At (2,2): s1[2]='a' == s2[2]='t'? No → min(1+dp[3][2], 1+dp[2][3]) = min(1+2, 1+3) = 3
- At (2,1): s1[2]='a' == s2[1]='a'? Yes → dp[3][2] = 2
- At (1,1): s1[1]='e' == s2[1]='a'? No → min(1+dp[2][1], 1+dp[1][2]) = min(1+2, 1+2) = 2
- At (0,0): s1[0]='s' == s2[0]='e'? No → min(1+dp[1][0], 1+dp[0][1]) = min(1+1, 1+1) = **2** ✓

# Tags
- Dynamic Programming
- Longest Common Subsequence
- String Comparison
- Tabulation

