## Problem

https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/description

```
```
You are given a string s and a positive integer k.

Select a set of non-overlapping substrings from the string s that satisfy the following conditions:

1. The length of each substring is at least k.
2. Each substring is a palindrome.

Return the maximum number of substrings in an optimal selection.

A substring is a contiguous sequence of characters within a string.

Example 1:
Input: s = "abaccdbbd", k = 3
Output: 2
Explanation: We can select the substrings underlined in s = "abaccdbbd". 
Both "aba" and "dbbd" are palindromes and have a length of at least k = 3.
It can be shown that we cannot find a selection with more than two valid substrings.

Example 2:
Input: s = "adbcda", k = 2
Output: 0
Explanation: There is no palindrome substring of length at least 2 in the string.

Constraints:
- 1 <= k <= s.length <= 2000
- s consists of lowercase English letters.
```

## Observations

1. **Palindrome Detection**: We need to identify all palindromic substrings efficiently. Since we have constraints of length at most 2000, we can use dynamic programming to precompute all palindromes in O(n²) time.

2. **Greedy Selection with DP**: This is an optimization problem where we want to maximize the count of non-overlapping palindromes. The key insight is that if we have palindromes at positions [i, j] and [j+1, k], we can independently decide whether to include each one.

3. **Non-overlapping Constraint**: Once we select a palindrome from index i to j, the next palindrome must start at j+1 or later. This suggests a recursive/DP approach where we process the string left to right.

4. **Minimum Length Constraint**: We only consider palindromes with length ≥ k, which simplifies our search space.

5. **Optimal Substructure**: The maximum number of palindromes we can select from index i onward depends only on what we choose from i onward, not on previous choices. This makes it suitable for dynamic programming.

## Solution

### Algorithm Overview

The solution uses two main components:

1. **Palindrome Precomputation**: Build a 2D DP table where `dp[i][j] = True` if substring s[i:j+1] is a palindrome.

2. **Recursive Selection with Memoization**: Use a memoized function F(i) that computes the maximum number of non-overlapping palindromes we can select starting from index i.

### Step 1: Build Palindrome DP Table

```python
dp = [[False] * n for _ in range(n)]
```

The table is built by:
- Marking single characters as palindromes: `dp[i][i] = True`
- Checking two-character palindromes: `s[i-1] == s[i]`
- Expanding around centers (odd-length palindromes):
  - Start from each position i, expand left and right while characters match
- Expanding around even centers (even-length palindromes):
  - For each two-character palindrome at [i-1, i], expand outward

This approach builds all palindromes in O(n²) time and space.

### Step 2: Recursive Function with Memoization

```python
def F(i: int) -> int:
    if i >= n:
        return 0  # Base case: no more characters to process
    
    if i in mem:
        return mem[i]  # Return cached result
    
    # Option 1: Skip current position, move to next
    res = F(i + 1)
    
    # Option 2: Try to select each palindrome starting at position i
    for j in range(i + k - 1, n):  # j is the end index of palindrome
        if dp[i][j]:  # If s[i:j+1] is a palindrome
            # Take this palindrome and continue from j+1
            res = max(res, 1 + F(j + 1))
    
    mem[i] = res
    return res
```

**Key insights**:
- We try two choices at each position: skip it or select a palindrome starting here
- When we select a palindrome from i to j, we jump to j+1 (non-overlapping constraint)
- We explore all possible palindromes starting at i with length ≥ k
- We memoize to avoid recalculating the same subproblems

### Time Complexity

- Palindrome detection: O(n²)
- Recursive calls: At most O(n) distinct states (i from 0 to n)
- For each state, we iterate O(n) possible endpoints
- Total: **O(n²)**

### Space Complexity

- DP table for palindromes: O(n²)
- Memoization table: O(n)
- Total: **O(n²)**

### Example Walkthrough

For s = "abaccdbbd", k = 3:

Palindromes of length ≥ 3:
- [0, 2]: "aba" ✓
- [2, 4]: "acc" ✓
- [5, 8]: "dbbd" ✓

Recursion F(0):
- Try skip index 0: F(1)
- Try "aba" [0,2]: 1 + F(3)
  - From F(3): "acc" [2,4] not valid (overlaps), "dbbd" [5,8] valid → 1 + F(9) = 1
  - Total: 1 + 1 = 2 ✓
- Maximum: 2

```

## Tags

#dynamic-programming #greedy #palindrome #memoization #string-processing
```

## Observations

## Solution

# Tags

