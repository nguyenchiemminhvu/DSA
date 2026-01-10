## Problem

https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/description/

```
Given two strings s1 and s2, return the lowest ASCII sum of deleted characters to make two strings equal.

Example 1:
Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.

Example 2:
Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d] + 101[e] + 101[e] to the sum.
Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.

Constraints:
- 1 <= s1.length, s2.length <= 1000
- s1 and s2 consist of lowercase English letters.
```

## Observations

1. **Goal**: Make two strings equal by deleting characters, minimizing the ASCII sum of deleted characters.

2. **Key Insight**: Instead of thinking about what to delete, think about what to **keep**. The characters we keep form a common subsequence.

3. **Mathematical Relationship**:
   - Total ASCII sum = sum(s1) + sum(s2)
   - Minimum deletion sum = Total sum - Maximum sum of common subsequence
   - The common subsequence appears in both strings, so its contribution is doubled when we calculate the total sum

4. **Why maximize common subsequence?**
   - If we maximize what we keep (common subsequence with maximum ASCII sum), we minimize what we delete
   - Example: s1="sea", s2="eat"
     - Total sum = (115+101+97) + (101+97+116) = 627
     - Common subsequence "ea" has ASCII sum = (101+97) = 198
     - Since "ea" appears in both strings, we save 2×198 = 396 from deletion
     - Minimum deletion = 627 - 396 = 231

5. **This is a variant of Longest Common Subsequence (LCS)**, but instead of maximizing length, we maximize ASCII sum.

## Solution

### Approach: Dynamic Programming with Memoization

**State Definition**:
- `F(i1, i2)` = maximum ASCII sum of common subsequence from `s1[0:i1+1]` and `s2[0:i2+1]`

**Base Case**:
- If `i1 < 0` or `i2 < 0`: return 0 (no characters to compare)

**Recurrence Relation**:
1. **If `s1[i1] == s2[i2]`**: 
   - The characters match, so include them in the common subsequence
   - Add their ASCII values (counted twice since they appear in both strings)
   - `F(i1, i2) = 2 × ord(s1[i1]) + F(i1-1, i2-1)`

2. **If `s1[i1] != s2[i2]`**:
   - Try skipping character from s1: `F(i1-1, i2)`
   - Try skipping character from s2: `F(i1, i2-1)`
   - Take the maximum: `F(i1, i2) = max(F(i1-1, i2), F(i1, i2-1))`

**Final Answer**:
```
minimum_deletion_sum = total_sum - F(len(s1)-1, len(s2)-1)
```

### Code Walkthrough

```python
class Solution:
    def minimumDeleteSum(self, s1: str, s2: str) -> int:
        # Calculate total ASCII sum of both strings
        total_sum = sum(ord(c) for c in s1) + sum(ord(c) for c in s2)
        memo = {}

        # F(i1, i2) -> biggest sum of common subsequence from s1[:i1+1] and s2[:i2+1]
        def F(i1: int, i2: int) -> int:
            # Base case: no more characters to compare
            if i1 < 0 or i2 < 0:
                return 0
            
            # Return memoized result if available
            if (i1, i2) in memo:
                return memo[(i1, i2)]
            
            max_so_far = 0
            if s1[i1] == s2[i2]:
                # Characters match: include both (hence 2x the ASCII value)
                max_so_far = max(max_so_far, ord(s1[i1]) + ord(s2[i2]) + F(i1-1, i2-1))
            else:
                # Characters don't match: try skipping from either string
                max_so_far = max([max_so_far, F(i1, i2-1), F(i1-1, i2)])
            
            memo[(i1, i2)] = max_so_far
            return max_so_far

        # Minimum deletion = Total sum - Maximum common subsequence sum
        return total_sum - F(len(s1) - 1, len(s2) - 1)
```

### Complexity Analysis

**Time Complexity**: O(m × n)
- m = length of s1, n = length of s2
- We compute at most m × n states
- Each state is computed once due to memoization

**Space Complexity**: O(m × n)
- Memoization dictionary stores at most m × n entries
- Recursion call stack depth is O(m + n) in the worst case

### Example Trace

For s1 = "sea", s2 = "eat":

```
Total sum = 313 + 314 = 627

F(2,2): s1[2]='a', s2[2]='t' → max(F(1,2), F(2,1)) 
F(1,2): s1[1]='e', s2[2]='t' → max(F(0,2), F(1,1))
F(2,1): s1[2]='a', s2[1]='a' → 97+97+F(1,0) = 194 + F(1,0)
F(1,1): s1[1]='e', s2[1]='a' → max(F(0,1), F(1,0))
F(1,0): s1[1]='e', s2[0]='e' → 101+101+F(0,-1) = 202
F(0,2): s1[0]='s', s2[2]='t' → max(F(-1,2), F(0,1)) = F(0,1)
F(0,1): s1[0]='s', s2[1]='a' → max(F(-1,1), F(0,0)) = F(0,0)
F(0,0): s1[0]='s', s2[0]='e' → max(F(-1,0), F(0,-1)) = 0

Building up:
F(0,0) = 0
F(0,1) = 0
F(1,0) = 202 (matched 'e')
F(1,1) = max(0, 202) = 202
F(2,1) = 194 + 202 = 396 (matched 'a')
F(1,2) = max(0, 202) = 202
F(2,2) = max(202, 396) = 396

Answer = 627 - 396 = 231
```

The maximum common subsequence sum is 396 (for "ea" appearing in both strings, counted as 2×(101+97) = 396), so the minimum deletion sum is 627 - 396 = 231.

# Tags

