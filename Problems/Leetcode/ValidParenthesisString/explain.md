## Problem

https://leetcode.com/problems/valid-parenthesis-string/

```
Given a string s containing only three types of characters: '(', ')' and '*', return true if s is valid.

The following rules define a valid string:

Any left parenthesis '(' must have a corresponding right parenthesis ')'.
Any right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string "".

Example 1:

Input: s = "()"
Output: true

Example 2:

Input: s = "(*)"
Output: true

Example 3:

Input: s = "(*))"
Output: true

Constraints:

1 <= s.length <= 100
s[i] is '(', ')' or '*'.
```

## Observations

1. **Core Challenge**: The asterisk `*` can be interpreted as `(`, `)`, or empty string, creating multiple possibilities at each asterisk position.

2. **Balance Tracking**: We need to track the balance of open parentheses. For a valid string:
   - Never have more closing than opening parentheses at any point
   - End with exactly zero unmatched opening parentheses

3. **State Space**: At each position, we need to track:
   - Current index in the string
   - Current count of unmatched opening parentheses

4. **Branching Factor**: Each asterisk creates 3 possible paths, leading to exponential time complexity without memoization.

5. **Constraints**: The problem size (≤100) makes dynamic programming feasible.

## Solution

### Approach 1: Memoized Recursion (Top-Down DP)

The provided solution uses a top-down dynamic programming approach with memoization:

```python
class Solution:
    def checkValidString(self, s: str) -> bool:
        n = len(s)
        memo = {}

        def dfs(i: int, count_open: int) -> bool:
            # Base cases
            if count_open < 0:  # Too many closing parentheses
                return False
            if i == n:  # End of string
                return count_open == 0
            
            # Check memoization
            if (i, count_open) in memo:
                return memo[(i, count_open)]
            
            # Process current character
            if s[i] == '(':
                res = dfs(i + 1, count_open + 1)
            elif s[i] == ')':
                res = dfs(i + 1, count_open - 1)
            else:  # asterisk '*'
                res = (dfs(i + 1, count_open) or      # treat as empty
                       dfs(i + 1, count_open + 1) or  # treat as '('
                       dfs(i + 1, count_open - 1))    # treat as ')'
            
            memo[(i, count_open)] = res
            return res
        
        return dfs(0, 0)
```

**Time Complexity**: O(n²) where n is the length of string
**Space Complexity**: O(n²) for memoization table

### Approach 2: Tabulation (Bottom-Up DP)

```python
def checkValidString_tabulation(s: str) -> bool:
    n = len(s)
    # dp[i][j] = can we have j open parentheses at position i
    dp = [[False] * (n + 1) for _ in range(n + 1)]
    dp[0][0] = True  # Base case: empty string with 0 open parens
    
    for i in range(1, n + 1):
        for j in range(n + 1):
            char = s[i - 1]
            
            if char == '(':
                if j > 0:
                    dp[i][j] = dp[i - 1][j - 1]
            elif char == ')':
                if j < n:
                    dp[i][j] = dp[i - 1][j + 1]
            else:  # asterisk
                # Treat as empty
                dp[i][j] = dp[i - 1][j]
                # Treat as '('
                if j > 0:
                    dp[i][j] = dp[i][j] or dp[i - 1][j - 1]
                # Treat as ')'
                if j < n:
                    dp[i][j] = dp[i][j] or dp[i - 1][j + 1]
    
    return dp[n][0]
```

**Time Complexity**: O(n²)
**Space Complexity**: O(n²)

### Approach 3: Greedy Solution

The most efficient approach uses a greedy strategy by tracking the range of possible open parentheses:

```python
def checkValidString_greedy(s: str) -> bool:
    # Track the range [min_open, max_open] of possible open parentheses
    min_open = max_open = 0
    
    for char in s:
        if char == '(':
            min_open += 1
            max_open += 1
        elif char == ')':
            min_open -= 1
            max_open -= 1
        else:  # asterisk
            min_open -= 1  # Best case: treat as ')'
            max_open += 1  # Worst case: treat as '('
        
        # If max_open < 0, too many ')' encountered
        if max_open < 0:
            return False
        
        # min_open should never go below 0
        min_open = max(min_open, 0)
    
    # At the end, we need exactly 0 open parentheses
    return min_open <= 0 <= max_open
```

**Time Complexity**: O(n)
**Space Complexity**: O(1)

## Algorithm Comparison

| Approach | Time | Space | Pros | Cons |
|----------|------|-------|------|------|
| Memoized Recursion | O(n²) | O(n²) | Intuitive, handles all cases clearly | Recursive overhead |
| Tabulation | O(n²) | O(n²) | No recursion, bottom-up approach | More complex state management |
| Greedy | O(n) | O(1) | Most efficient, elegant | Requires insight into range tracking |

## Key Insights

1. **Memoization**: The recursive solution avoids redundant calculations by caching results for each (position, open_count) state.

2. **Tabulation**: Bottom-up DP fills the table systematically, ensuring all dependencies are resolved before computing current state.

3. **Greedy Optimization**: Instead of exploring all possibilities, we track the range of valid open parentheses counts, pruning impossible branches early.

4. **State Pruning**: In the greedy approach, maintaining `min_open >= 0` eliminates invalid states where we have too many closing parentheses.

## Tags

array, string, greedy, dynamic programming