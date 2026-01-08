## Problem

https://leetcode.com/problems/longest-common-subsequence/description/

```
Given two strings text1 and text2, return the length of their longest common subsequence. 
If there is no common subsequence, return 0.

A subsequence of a string is a new string generated from the original string with some 
characters (can be none) deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.

Example 1:
Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.

Example 2:
Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.

Example 3:
Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.

Constraints:
- 1 <= text1.length, text2.length <= 1000
- text1 and text2 consist of only lowercase English characters.
```

## Observations

1. **Subsequence vs Substring**: A subsequence doesn't need to be contiguous - we can skip characters but must maintain order.

2. **Two Pointer Approach Won't Work**: We can't simply use two pointers because when characters don't match, we don't know which string to advance.

3. **Recursive Nature**: At each position, we have a decision to make:
   - If characters match: we can include this character in our LCS
   - If they don't match: we need to try skipping a character from either string

4. **Optimal Substructure**: The LCS of two strings can be built from the LCS of their prefixes:
   - If `s1[i] == s2[j]`: LCS(i, j) = 1 + LCS(i-1, j-1)
   - If `s1[i] != s2[j]`: LCS(i, j) = max(LCS(i-1, j), LCS(i, j-1))

5. **Overlapping Subproblems**: The same subproblems (comparing the same prefixes) will be computed multiple times, making this perfect for memoization/DP.

## Solution

### Approach: Top-Down Dynamic Programming (Memoization)

**Key Idea**: Define a recursive function `F(i1, i2)` that returns the length of the longest common subsequence of `s1[:i1+1]` and `s2[:i2+1]`.

**Recurrence Relation**:
```
F(i1, i2) = {
    0                           if i1 < 0 or i2 < 0
    1 + F(i1-1, i2-1)          if s1[i1] == s2[i2]
    max(F(i1-1, i2), F(i1, i2-1))   if s1[i1] != s2[i2]
}
```

**Base Case**: When either index is negative (out of bounds), there are no characters to compare, so LCS length is 0.

**Recursive Cases**:
1. **Characters Match** (`s1[i1] == s2[i2]`): 
   - We found a common character! Include it in our subsequence.
   - Add 1 to the LCS of the remaining prefixes: `1 + F(i1-1, i2-1)`

2. **Characters Don't Match** (`s1[i1] != s2[i2]`):
   - We need to try both options:
     - Skip character at i1 from s1: `F(i1-1, i2)`
     - Skip character at i2 from s2: `F(i1, i2-1)`
   - Take the maximum of both options

**Memoization**: Store computed results in a dictionary `memo` with key `(i1, i2)` to avoid recomputing the same subproblems.

### Implementation

```python
class Solution:
    def longestCommonSubsequence(self, s1: str, s2: str) -> int:
        n1 = len(s1)
        n2 = len(s2)
        memo = {}

        # F(i1, i2) -> longest common subsequence of s1[:i1+1] and s2[:i2+1]
        def F(i1: int, i2: int) -> int:
            if i1 < 0 or i2 < 0:
                return 0
            
            if (i1, i2) in memo:
                return memo[(i1, i2)]
            
            max_so_far = 0
            if s1[i1] == s2[i2]:
                max_so_far = 1 + F(i1 - 1, i2 - 1)
            else:
                max_so_far = max(F(i1, i2 - 1), F(i1 - 1, i2))
            
            memo[(i1, i2)] = max_so_far
            return max_so_far
        
        return F(n1 - 1, n2 - 1)
```

### Complexity Analysis

**Time Complexity**: O(n1 × n2)
- We have n1 × n2 unique subproblems (all combinations of indices)
- Each subproblem is computed once and cached
- Each computation does O(1) work

**Space Complexity**: O(n1 × n2)
- Memoization dictionary stores up to n1 × n2 entries
- Recursion call stack depth is O(n1 + n2) in the worst case

### Example Walkthrough

For `text1 = "abcde"`, `text2 = "ace"`:

```
Starting from F(4, 2):
  s1[4]='e', s2[2]='e' → match!
  F(4, 2) = 1 + F(3, 1)
  
  s1[3]='d', s2[1]='c' → no match
  F(3, 1) = max(F(2, 1), F(3, 0))
  
  s1[2]='c', s2[1]='c' → match!
  F(2, 1) = 1 + F(1, 0)
  
  s1[1]='b', s2[0]='a' → no match
  F(1, 0) = max(F(0, 0), F(1, -1))
  
  s1[0]='a', s2[0]='a' → match!
  F(0, 0) = 1 + F(-1, -1) = 1 + 0 = 1
  
  F(1, -1) = 0 (base case)
  F(1, 0) = max(1, 0) = 1
  F(2, 1) = 1 + 1 = 2
  
  Continue building up...
  Final answer: 3
```

The LCS is "ace" with length 3.

### Alternative: Bottom-Up DP

A bottom-up (tabulation) approach would build a 2D table iteratively, which can be more space-efficient (can optimize to O(min(n1, n2)) space).

# Tags

`Dynamic Programming` `Memoization` `String` `Top-Down DP` `Classic DP Problem`

