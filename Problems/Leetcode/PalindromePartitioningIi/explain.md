## Problem

https://leetcode.com/problems/palindrome-partitioning-ii/description

Given a string `s`, partition `s` such that every substring of the partition is a palindrome.

**Return the minimum cuts needed for a palindrome partitioning of `s`.**

### Examples

**Example 1:**
- Input: `s = "aab"`
- Output: `1`
- Explanation: The palindrome partitioning `["aa","b"]` could be produced using 1 cut.

**Example 2:**
- Input: `s = "a"`
- Output: `0`

**Example 3:**
- Input: `s = "ab"`
- Output: `1`

### Constraints

- $1 \leq \text{s.length} \leq 2000$
- `s` consists of lowercase English letters only

## Observations

1. **Palindrome Identification is Key**: To find minimum cuts, we need to quickly identify which substrings are palindromes. Building a 2D DP table `dp[i][j]` that tracks whether `s[i...j]` is a palindrome is essential.

2. **Palindrome Building Strategy**: We can build the palindrome table efficiently by:
   - Single characters are always palindromes: `dp[i][i] = True`
   - Two consecutive characters: Check if `s[i-1] == s[i]`
   - Expanding from centers (odd and even length palindromes)

3. **Two-Phase Approach**:
   - **Phase 1**: Build complete palindrome lookup table ($O(n^2)$)
   - **Phase 2**: Use memoized recursion to find minimum cuts ($O(n^2)$)

4. **Recursive Structure**: For position `i`, if `s[0...i]` is a palindrome, we need 0 cuts. Otherwise, we try all possible last palindromes ending at `i`, and take the minimum: 
   $$F(i) = \min(1 + F(j-1)) \text{ for all } j \text{ where } dp[j][i] = \text{True}$$

5. **Time Complexity**: $O(n^2)$ for building palindromes + $O(n^2)$ for memoized recursion = $O(n^2)$ total

6. **Space Complexity**: $O(n^2)$ for palindrome table + $O(n)$ for memoization cache + $O(n)$ recursion stack = $O(n^2)$

## Solution

### Algorithm Breakdown

**Step 1: Build Palindrome Table**
```python
# Mark single characters as palindromes
for i in range(n):
    dp[i][i] = True
    if i > 0 and s[i-1] == s[i]:
        dp[i-1][i] = True

# Expand around centers
# Odd-length palindromes
for i in range(n):
    l, r = i - 1, i + 1
    while l >= 0 and r < n and s[l] == s[r]:
        dp[l][r] = True
        l -= 1
        r += 1

# Even-length palindromes
for i in range(n):
    if i > 0 and dp[i-1][i]:
        l, r = i - 2, i + 1
        while l >= 0 and r < n and s[l] == s[r]:
            dp[l][r] = True
            l -= 1
            r += 1
```

**Step 2: Find Minimum Cuts Using Memoized Recursion**

The function `F(i)` returns the minimum cuts needed to partition `s[0...i]`:
- **Base case**: If `i < 0`, return 0 (empty string needs 0 cuts)
- **Optimized case**: If `dp[0][i]` is True (entire prefix is palindrome), return 0
- **Recursive case**: Try splitting at every possible position `j` where `dp[j][i]` is True:
  - The last segment is `s[j...i]` (which is a palindrome)
  - The first part needs `F(j-1)` cuts
  - We need 1 additional cut to separate them
  - Take the minimum across all valid splits

**Memoization**: Store results in `mem` dictionary to avoid recomputing the same subproblems.

### Trace Through Example: `s = "aab"`

**Palindrome Table:**
```
  a a b
a T T F
a   T F
b       T
```

**Memoized Recursion:**
- `F(2)` (index 2, "aab"):
  - Check if `dp[0][2]` = False → not a palindrome
  - Try j=1: `dp[1][2]` = False → "ab" not a palindrome
  - Try j=2: `dp[2][2]` = True → "b" is palindrome, compute `1 + F(1)`
  
- `F(1)` (index 1, "aa"):
  - Check if `dp[0][1]` = True → "aa" is a palindrome
  - Return 0 (no cuts needed)

- `F(2)` = `1 + F(1)` = `1 + 0` = **1**

### Key Insights

- The palindrome table allows $O(1)$ lookup of whether any substring is a palindrome
- Memoization prevents redundant calculations of subproblems
- The expansion-around-center approach efficiently builds the palindrome table without checking all $O(n^2)$ substrings redundantly
- Even-length palindrome expansion reuses the `dp[i-1][i]` computed earlier for efficiency

# Tags

- Dynamic Programming
- String
- Memoization
- Palindrome
- LeetCode Hard

