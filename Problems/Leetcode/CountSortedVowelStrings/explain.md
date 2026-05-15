## Problem

https://leetcode.com/problems/count-sorted-vowel-strings/description/

# Count Sorted Vowel Strings

## Problem

https://leetcode.com/problems/count-sorted-vowel-strings/description/

Given an integer `n`, return the number of strings of length `n` that consist only of vowels (a, e, i, o, u) and are lexicographically sorted.

A string `s` is lexicographically sorted if for all valid `i`, `s[i]` is the same as or comes before `s[i+1]` in the alphabet.

### Examples

**Example 1:**
- Input: `n = 1`
- Output: `5`
- Explanation: The 5 sorted strings are `["a","e","i","o","u"]`

**Example 2:**
- Input: `n = 2`
- Output: `15`
- Explanation: The 15 sorted strings are `["aa","ae","ai","ao","au","ee","ei","eo","eu","ii","io","iu","oo","ou","uu"]`

**Example 3:**
- Input: `n = 33`
- Output: `66045`

### Constraints

- `1 <= n <= 50`

## Observations

1. **Lexicographically Sorted Constraint**: Since the string must be lexicographically sorted, once we choose a vowel at position `i`, all subsequent vowels at position `i+1` and beyond must be greater than or equal to it. This eliminates invalid combinations like "ea".

2. **Combination Problem**: This is essentially a **combination with replacement** problem. We're choosing `n` items from 5 vowels where order matters (but only in a non-decreasing sense).

3. **Recursive Structure**: 
   - At each position, we can either:
     - Skip the current vowel and move to the next one (choosing vowel at index `io+1` or later)
     - Use the current vowel and fill the next position (choosing the same or later vowel)
   
4. **Mathematical Insight**: The number of non-decreasing sequences of length `n` from 5 elements equals the number of ways to distribute `n` identical items into 5 distinct bins, which is **C(n+4, 4)** or **C(n+4, n)** using stars and bars formula.

5. **Memoization vs DP**: The recursive approach with memoization can work, but the bottom-up DP approach is more efficient and avoids stack overflow risks for large `n`.

## Solution Explanation

### Approach: Bottom-Up Dynamic Programming

**Key Insight**: Build the solution by computing how many valid strings of length `i` end with vowel index `io` or later.

**State Definition**:
- `dp[i][io]` = number of valid strings of length `i` that start from vowel at index `io` or later
  - `i` ranges from `0` to `n` (string length)
  - `io` ranges from `0` to `5` (vowel index)

**Recurrence Relation**:
```
dp[i][io] = dp[i][io+1] + dp[i+1][io]
```

- `dp[i][io+1]`: Skip the current vowel, use vowels at index `io+1` or later
- `dp[i+1][io]`: Use the current vowel at index `io`, then fill remaining `i+1` positions

**Base Case**:
- `dp[n][io] = 1` for all `io` (strings of length `n` have exactly 1 way if we've filled all positions)

**Direction**: Work backwards from position `n-1` to `0`, and from vowel index `no-1` to `0`

### Time Complexity
- **O(n × 5)** = **O(n)** - We fill a 2D table of size `(n+1) × 6`

### Space Complexity
- **O(n × 5)** = **O(n)** - We store a 2D DP table

### Example Trace (n=2)

```
Initial: dp[2][*] = [1, 1, 1, 1, 1, 1]

i=1:
  io=4: dp[1][4] = dp[1][5] + dp[2][4] = 1 + 1 = 2
  io=3: dp[1][3] = dp[1][4] + dp[2][3] = 2 + 1 = 3
  io=2: dp[1][2] = dp[1][3] + dp[2][2] = 3 + 1 = 4
  io=1: dp[1][1] = dp[1][2] + dp[2][1] = 4 + 1 = 5
  io=0: dp[1][0] = dp[1][1] + dp[2][0] = 5 + 1 = 6

i=0:
  io=4: dp[0][4] = dp[0][5] + dp[1][4] = 1 + 2 = 3
  io=3: dp[0][3] = dp[0][4] + dp[1][3] = 3 + 3 = 6
  io=2: dp[0][2] = dp[0][3] + dp[1][2] = 6 + 4 = 10
  io=1: dp[0][1] = dp[0][2] + dp[1][1] = 10 + 5 = 15
  io=0: dp[0][0] = dp[0][1] + dp[1][0] = 15 + 6 = 21

Answer: dp[0][0] = 15 ✓
```

## Tags

- Dynamic Programming
- Combinatorics
- Memoization
- Bottom-up DP
- String Generation

## Observations

## Solution

# Tags

