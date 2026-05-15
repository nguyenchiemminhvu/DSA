## Problem

https://leetcode.com/problems/decode-ways/description/

A secret message is encoded as a string of digits with the following mapping:
- "1" → 'A', "2" → 'B', ..., "25" → 'Y', "26" → 'Z'

Since some codes are contained in other codes (e.g., "2" and "5" are both valid, as is "25"), there can be multiple valid decodings of the same string.

**Examples:**
- "11106" can be decoded as:
  - "AAJF" (1, 1, 10, 6)
  - "KJF" (11, 10, 6)
  - NOT valid: (1, 11, 06) because "06" has a leading zero

**Task:** Given a string `s` of only digits, return the number of ways to decode it. Return 0 if impossible.

**Constraints:**
- 1 ≤ s.length ≤ 100
- s contains only digits (may have leading zeros)
- Answer fits in a 32-bit integer

## Observations

1. **Valid Codes:** Only "1"-"26" are valid codes. "0" alone is invalid, and any code with a leading zero (like "06") is invalid.

2. **Greedy Doesn't Work:** We cannot greedily choose the longest valid code at each step. For example, in "226":
   - Greedy approach: (22, 6) → only 1 way
   - Actual: (2, 26), (22, 6), (2, 2, 6) → 3 ways

3. **Overlapping Subproblems:** At each position, we have at most 2 choices:
   - Take the next 1 digit (if valid)
   - Take the next 2 digits (if valid)
   - This leads to a recursive structure with overlapping subproblems

4. **State Definition:** 
   - `F(i)` = number of ways to decode `s[i:]` (the substring starting at index i)
   - Base case: `F(n) = 1` (empty string has 1 way to decode: empty)

5. **Recurrence:**
   ```
   F(i) = F(i+1) [if s[i:i+1] is valid]
        + F(i+2) [if s[i:i+2] is valid]
   ```

6. **Dynamic Programming:** Bottom-up DP avoids recursion overhead. Build the table from right to left.

7. **Edge Cases:**
   - Leading zeros: "06" → 0 ways
   - All zeros after valid prefix: "100" → 0 ways
   - Single "0": "0" → 0 ways

## Solution

**Approach:** Bottom-up Dynamic Programming

**Algorithm:**
1. Create a valid set of codes: {"1", "2", ..., "26"}
2. Initialize `dp[n] = 1` and `dp[n+1] = 1` (base case)
3. Iterate from position `n-1` down to 0:
   - Check if `s[i]` (single digit) is valid → add `dp[i+1]`
   - Check if `s[i:i+2]` (two digits) is valid → add `dp[i+2]`
4. Return `dp[0]`

**Time Complexity:** O(n) - single pass through the string
**Space Complexity:** O(n) - DP array of size n+2

**Why this works:**
- `dp[i]` stores the number of ways to decode from position `i` to the end
- By processing right-to-left, we ensure all future states (i+1, i+2) are computed before current state
- Each position's answer depends only on the next 1-2 positions, making DP optimal

**Example walkthrough for "226":**
```
s = "226", n = 3, encoded = {"1"..."26"}

dp[3] = 1, dp[4] = 1  (base cases)

i=2: s[2]='6'
  - s[2:3]='6' in encoded → dp[2] += dp[3] = 1
  - i+2=4 > n, skip
  - dp[2] = 1

i=1: s[1]='2'
  - s[1:2]='2' in encoded → dp[1] += dp[2] = 1
  - s[1:3]='26' in encoded → dp[1] += dp[3] = 1
  - dp[1] = 2

i=0: s[0]='2'
  - s[0:1]='2' in encoded → dp[0] += dp[1] = 2
  - s[0:2]='22' in encoded → dp[0] += dp[2] = 1
  - dp[0] = 3

Answer: dp[0] = 3 ✓
```

# Tags

#dynamic-programming #string-manipulation #memoization #bottom-up-dp #decode
