## Problem

https://leetcode.com/problems/wildcard-matching/description

Implement wildcard pattern matching with support for '?' and '*' where:
- `?` matches any single character
- `*` matches any sequence of characters (including the empty sequence)

The matching should cover the **entire input string** (not partial).

### Examples

**Example 1:**
- Input: `s = "aa", p = "a"`
- Output: `false`
- Explanation: "a" does not match the entire string "aa"

**Example 2:**
- Input: `s = "aa", p = "*"`
- Output: `true`
- Explanation: '*' matches any sequence

**Example 3:**
- Input: `s = "cb", p = "?a"`
- Output: `false`
- Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'

### Constraints
- $0 \leq s.\text{length}, p.\text{length} \leq 2000$
- `s` contains only lowercase English letters
- `p` contains only lowercase English letters, '?' or '*'

## Observations

### Key Insights

1. **Matching Semantics**
   - `?` is straightforward: it matches exactly one character, so we advance both pointers
   - `*` is tricky: it can match 0 or more characters, giving us multiple options to explore

2. **Wildcard Star (`*`) Cases**
   - Match 0 characters: Move pattern pointer forward `p[idx_p+1]`, keep string pointer at `s[idx_s]`
   - Match 1 character: Move both pointers forward by 1
   - Match multiple characters: Move string pointer, keep pattern pointer at the same `*`

3. **Base Cases**
   - If we've consumed the entire string (`idx_s >= ns`), we succeed only if the remaining pattern contains only `*`
   - If we've consumed the entire pattern (`idx_p >= np`), we succeed only if we've also consumed the entire string

4. **Problem Structure**
   - This is an optimal substructure problem where the result depends on smaller subproblems
   - The state space is defined by two indices: position in string and position in pattern
   - This naturally suggests dynamic programming or memoized recursion

5. **Complexity Trade-offs**
   - Naive recursive solution without memoization: exponential time (especially with `*`)
   - Memoized recursion: $O(n \times m)$ time and space where $n = |s|, m = |p|$
   - Bottom-up DP: $O(n \times m)$ time and $O(n \times m)$ space, more efficient than recursion overhead

## Solution

### Approach: Bottom-Up Dynamic Programming

We use a 2D DP table where `dp[i][j]` represents whether the first `i` characters of string `s` match the first `j` characters of pattern `p`.

#### Algorithm Steps

1. **Initialize DP Table**
   - Create a `(ns+1) × (np+1)` table
   - `dp[i][np]` = True if `i >= ns` (empty pattern matches only empty string or when we've fully consumed `s`)
   - `dp[ns][j]` = True if remaining pattern contains only `*` characters (since `*` can match empty sequence)

2. **Fill the Table (Bottom-Up)**
   - Process indices from right to left (from the end backwards)
   - For each position `(i, j)`:
     - If `p[j] == '?'`: matches single character, so `dp[i][j] = dp[i+1][j+1]`
     - If `p[j] == '*'`: has three options:
       - Match 0 characters: `dp[i][j+1]` (skip this `*`)
       - Match 1 character: `dp[i+1][j+1]` (consume one char and advance pattern)
       - Match multiple characters: `dp[i+1][j]` (consume one char, keep `*`)
       - Result: OR of all three options
     - Otherwise (regular character): must match exactly, so `dp[i][j] = (s[i] == p[j]) and dp[i+1][j+1]`

3. **Return Result**
   - `dp[0][0]` tells us if the entire string matches the entire pattern

#### Complexity Analysis

- **Time Complexity**: $O(n \times m)$ where $n = |s|$ and $m = |p|$
  - We fill each cell of the DP table exactly once
  - Each cell computation is $O(1)$ (except base case initialization with star check)
  
- **Space Complexity**: $O(n \times m)$
  - The 2D DP table requires $(n+1) \times (m+1)$ space
  - Can be optimized to $O(m)$ with rolling array technique, but not necessary given constraints

#### Implementation

```python
class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        ns = len(s)
        np = len(p)
        
        # Create DP table: dp[i][j] means s[0:i] matches p[0:j]
        dp = [[False] * (np + 1) for _ in range(ns + 1)]
        
        # Base cases: when string is exhausted
        for idx_s in range(ns + 1):
            dp[idx_s][np] = (idx_s >= ns)  # Only empty pattern matches empty string
        
        # Base cases: when pattern is exhausted
        # Remaining pattern must be all '*' to match remaining string
        for idx_p in range(np + 1):
            dp[ns][idx_p] = (idx_p >= np) or all(c == '*' for c in p[idx_p:])
        
        # Fill DP table from bottom-right to top-left
        for idx_s in range(ns - 1, -1, -1):
            for idx_p in range(np - 1, -1, -1):
                if p[idx_p] == '?':
                    # '?' matches any single character
                    dp[idx_s][idx_p] = dp[idx_s + 1][idx_p + 1]
                elif p[idx_p] == '*':
                    # '*' can match:
                    # - 0 characters: dp[idx_s][idx_p + 1]
                    # - 1+ characters: dp[idx_s + 1][idx_p]
                    # - OR match 1 char and advance pattern: dp[idx_s + 1][idx_p + 1]
                    dp[idx_s][idx_p] = dp[idx_s + 1][idx_p + 1] or dp[idx_s + 1][idx_p] or dp[idx_s][idx_p + 1]
                else:
                    # Regular character must match exactly
                    dp[idx_s][idx_p] = (s[idx_s] == p[idx_p]) and dp[idx_s + 1][idx_p + 1]
        
        return dp[0][0]
```

#### Example Trace

Let's trace `s = "ab"`, `p = "*?b"`:

```
    ""  *   ?   b
""   T   T   F   F
a    T   T   T   F
b    T   T   F   T
```

Reading process:
- `dp[2][3]`: s="ab", p="*?b" → check last chars: 'b'=='b' ✓ and `dp[3][4]=T` → `dp[2][3]=T`
- `dp[2][2]`: s="ab", p="*?" → 'b'!='?' ✗ → `dp[2][2]=F`
- `dp[2][1]`: s="ab", p="*" → '*' options: `dp[2][2]` or `dp[3][1]` → `T or T = T`
- And so on...

#### Why This Approach Works

The DP approach captures all possible matching strategies:
- For each `*`, we track whether matching 0 chars, 1 char, or multiple chars leads to a valid match
- By filling backwards, each cell has all its dependencies already computed
- The recurrence naturally encodes the matching rules

# Tags

`dynamic-programming` `string-matching` `pattern-matching` `greedy-algorithm` `memoization`