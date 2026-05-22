## Problem

https://leetcode.com/problems/regular-expression-matching/description/

Given an input string `s` and a pattern `p`, implement regular expression matching with support for `'.'` and `'*'` where:

- `'.'` Matches any single character.
- `'*'` Matches zero or more of the preceding element.

Return a boolean indicating whether the matching covers the **entire** input string (not partial).

**Examples:**

1. `s = "aa"`, `p = "a"` → `false` (pattern doesn't match the entire string)
2. `s = "aa"`, `p = "a*"` → `true` ('*' allows 'a' to repeat)
3. `s = "ab"`, `p = ".*"` → `true` ('.*' matches any sequence)

**Constraints:**
- `1 <= s.length <= 20`
- `1 <= p.length <= 20`
- `s` contains only lowercase English letters
- `p` contains only lowercase English letters, `'.'`, and `'*'`
- For each `'*'`, there exists a valid preceding character

## Observations

### 1. **Pattern structure with '*' operator**
The `'*'` operator always follows a character and has two interpretations:
- **Zero occurrences**: Skip the character-asterisk pair in the pattern (match without consuming this pair)
- **One or more occurrences**: Consume one character from `s` and stay at the same pattern position to potentially match more

### 2. **Backward vs. Forward approach**
This solution uses **backward recursion** (from end to beginning):
- Process from the last characters of both `s` and `p`
- State: `F(idx_s, idx_p)` returns whether `s[0:idx_s+1]` matches `p[0:idx_p+1]`
- This is intuitive because we can first decide how to handle the last pattern character(s)

### 3. **Base cases are critical**
- When `idx_s < 0`: We've matched all of `s`. Pattern must also be fully matched or have only zero-match patterns remaining
- When `idx_p < 0`: Pattern is exhausted. Only valid if `s` is also exhausted (`idx_s < 0`)

### 4. **Character matching with '.' wildcard**
- `'.'` matches any single character, simplifying the logic: `s[idx_s] == target_ch or target_ch == '.'`
- This allows a single condition to handle both regular characters and wildcards

### 5. **Memoization is essential**
With overlapping subproblems (e.g., `s="aab"`, `p="c*a*b"`), the same `(idx_s, idx_p)` state is reached multiple times. Memoization reduces exponential complexity to polynomial.

## Solution

### Approach: **Backward Recursive DP with Memoization**

**Time Complexity:** $O(n \times m)$ where $n = |s|$ and $m = |p|$  
**Space Complexity:** $O(n \times m)$ for memoization table + recursion stack

```python
class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        ns = len(s)
        np = len(p)
        
        mem = {}
        
        def F(idx_s: int, idx_p: int) -> bool:
            # Base case 1: Both strings exhausted
            if idx_s < 0:
                if idx_p < 0:
                    return True
                # Pattern still has characters: check if remaining is all zero-match patterns
                if idx_p >= 1 and p[idx_p] == '*':
                    return F(idx_s, idx_p - 2)  # Skip the character-* pair
                return False
            
            # Base case 2: Pattern exhausted but string remains
            if idx_p < 0:
                return idx_s < 0
            
            # Memoization lookup
            if (idx_s, idx_p) in mem:
                return mem[(idx_s, idx_p)]
            
            res = False
            
            if p[idx_p] == '*':
                # Case 1: Match zero occurrences - skip the preceding char and '*'
                target_ch = p[idx_p - 1]
                res = res or F(idx_s, idx_p - 2)
                
                # Case 2: Match one or more occurrences
                if s[idx_s] == target_ch or target_ch == '.':
                    res = res or F(idx_s - 1, idx_p)
            
            elif p[idx_p] == '.' or s[idx_s] == p[idx_p]:
                # Single character match (either wildcard or exact character)
                res = res or F(idx_s - 1, idx_p - 1)
            else:
                # Characters don't match and no wildcard
                res = False
            
            mem[(idx_s, idx_p)] = res
            return res
        
        return F(ns - 1, np - 1)
```

### Step-by-step Walkthrough

**Example: `s = "aa"`, `p = "a*"`**

```
F(1, 2):  idx_s=1 (s[1]='a'), idx_p=2 (p[2]='*')
  → p[2]='*', target_ch = p[1]='a'
  → Try zero match: F(1, 0) → p[0]='a', s[1]='a' match → F(0, -1)
    → idx_p < 0, idx_s >= 0 → false
  → Try one+ match: s[1]='a' == 'a' → F(0, 2)
    → F(0, 2): idx_s=0, idx_p=2
      → p[2]='*', target_ch='a'
      → Zero match: F(0, 0) → F(-1, -1) → true ✓
```

### Key Algorithm Insights

1. **Pattern with '*' has flexibility**: We explore both possibilities (zero and one+ matches) and use `or` to succeed if either works

2. **Backward recursion simplifies '.' handling**: By going right-to-left, we can immediately recognize when the pattern position has '*' and what the target character is

3. **Memoization prevents redundant work**: A state like `(idx_s=2, idx_p=3)` computed once is never recomputed

4. **Base case for remaining pattern**: When `idx_s < 0` but `idx_p >= 0`, only patterns like `a*b*c*...` (with every character followed by '*') can match the empty remaining string

# Tags

- Dynamic Programming (Top-down/Memoization)
- String Matching
- Recursion with Memoization
- Regular Expression
- Backtracking

