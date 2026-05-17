## Problem

https://leetcode.com/problems/longest-ideal-subsequence/description

Given a string `s` consisting of lowercase letters and an integer `k`, find the length of the longest **ideal subsequence** of `s`.

A string `t` is **ideal** if:
1. `t` is a subsequence of `s` (can be derived by deleting some/no characters without changing order)
2. The absolute difference in alphabet order of every two **adjacent letters** in `t` is at most `k`

**Example 1:**
- Input: `s = "acfgbd"`, `k = 2`
- Output: `4`
- Explanation: The longest ideal string is `"acbd"` (length 4). Note: `"acfgbd"` is not ideal because `|'c' - 'f'| = 3 > k = 2`

**Example 2:**
- Input: `s = "abcd"`, `k = 3`
- Output: `4`
- Explanation: The longest ideal string is `"abcd"`

**Constraints:**
- $1 \leq |s| \leq 10^5$
- $0 \leq k \leq 25$
- `s` consists of lowercase English letters

## Observations

1. **This is a Dynamic Programming problem** - We need to find the longest subsequence satisfying constraints, which suggests DP.

2. **State definition** - `dp[i]` = length of the longest ideal subsequence ending at position `i` (character `s[i]`).

3. **Transition key insight** - For each position `i`, we can extend any previous subsequence ending at character `c` where `|ord(s[i]) - ord(c)| <= k`. This only requires tracking the **last occurrence** of each character.

4. **Alphabet constraint** - Since we only care about characters within distance `k` from current character, we can iterate through the range `[ord(s[i]) - k, ord(s[i]) + k]` instead of scanning all previous positions.

5. **Optimization** - Using `last_idx` dictionary to track the most recent position of each character avoids redundant comparisons (O(26k) per position instead of O(n) per position).

6. **Why we update `last_idx[s[i]]`** - We only need the most recent occurrence of each character because a more recent occurrence will always give us a longer subsequence.

## Solution

**Approach: Dynamic Programming with Character Tracking**

```python
class Solution:
    def longestIdealString(self, s: str, k: int) -> int:
        n = len(s)
        
        # dp[i] = length of longest ideal subsequence ending at index i
        dp = [1] * n  # Every single character is a valid ideal string of length 1
        res = 1       # At least one character
        
        # last_idx[ch] = most recent index where character ch appeared
        last_idx = {}
        
        for i in range(n):
            ival = ord(s[i])  # ASCII value of current character
            
            # Check all characters within distance k (both directions)
            for j in range(ival - k, ival + k + 1):
                jch = chr(j)  # Character at distance j from current char
                
                # If we've seen this character before, try to extend that subsequence
                if jch in last_idx:
                    jidx = last_idx[jch]  # Most recent position of character jch
                    dp[i] = max(dp[i], 1 + dp[jidx])
            
            # Record the most recent position of character s[i]
            last_idx[s[i]] = i
            
            # Track the overall maximum
            res = max(res, dp[i])
        
        return res
```

**Time Complexity:** $O(n \cdot k)$ where $n$ is the length of string and $k$ is the constraint value (at most 26)
- For each of $n$ positions, we iterate through at most $2k + 1$ characters in the range

**Space Complexity:** $O(n + 26) = O(n)$
- `dp` array of size $n$
- `last_idx` dictionary with at most 26 entries (one per lowercase letter)

**Why this works:**

1. **Greedy last occurrence** - We only track the most recent occurrence of each character because:
   - If character 'a' appeared at positions 2 and 5, and we're at position 10
   - Position 5 will always give us a longer subsequence than position 2 (since `dp[5] >= dp[2]`)
   - Therefore we only need to track position 5

2. **Range-based iteration** - Instead of checking all previous positions, we check only characters in the valid range `[s[i] - k, s[i] + k]`:
   - Any character outside this range violates the constraint
   - This limits iterations to $2k + 1$ characters maximum

3. **DP transition** - For position `i`, the longest ideal subsequence is either:
   - Starting fresh with just `s[i]` (length 1)
   - Extending from the last occurrence of any valid character `c` where `|s[i] - c| <= k`

# Tags
- Dynamic Programming
- Hash Map / Dictionary
- Greedy (tracking last occurrence)
- Subsequence

