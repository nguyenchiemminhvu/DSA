## Problem

https://leetcode.com/problems/splitting-a-string-into-descending-consecutive-values/description/

You are given a string `s` that consists of only digits.

Check if we can split `s` into **two or more** non-empty substrings such that the numerical values of the substrings are in **descending order** and the **difference** between numerical values of every two **adjacent** substrings is equal to **1**.

### Examples

**Example 1:**
- **Input:** `s = "1234"`
- **Output:** `false`
- **Explanation:** There is no valid way to split s.

**Example 2:**
- **Input:** `s = "050043"`
- **Output:** `true`
- **Explanation:** s can be split into `["05", "004", "3"]` with numerical values `[5, 4, 3]`. The values are in descending order with adjacent values differing by 1.

**Example 3:**
- **Input:** `s = "9080701"`
- **Output:** `false`
- **Explanation:** There is no valid way to split s.

**Additional Examples:**
- `s = "0090089"` can be split into `["0090", "089"]` with values `[90, 89]` ✓
- `s = "001"` can be split into `["0", "01"]`, `["00", "1"]`, or `["0", "0", "1"]` with values `[0, 1]`, `[0, 1]`, and `[0, 0, 1]` respectively - all invalid ✗

### Constraints
- `1 <= s.length <= 20`
- `s` only consists of digits

## Observations

1. **Minimum Split Requirement:** We need at least 2 substrings, so we must find at least one valid split point.

2. **Descending by 1:** Each subsequent value must be exactly 1 less than the previous value (not just descending).

3. **Leading Zeros Matter:** Substrings like "0090", "089", "050" have numerical values 90, 89, 50 respectively. Leading zeros don't affect the numerical value.

4. **Search Space:** 
   - With a string of length n, there are many ways to split it
   - We need to try different starting points for the first two values
   - Once we fix the first two values, the pattern is determined

5. **Backtracking Approach:**
   - Try all possible lengths for the first substring
   - For each first substring, try all possible lengths for the second substring
   - If `first_value == second_value + 1`, continue searching with DFS
   - The DFS will try to extend the sequence by finding the next value that's exactly 1 less

6. **Early Termination:**
   - If we reach the end of the string (consumed all characters), return true
   - If we can't find a valid next substring at any position, backtrack

## Solution

### Approach: Backtracking with DFS

The solution uses a two-phase approach:

**Phase 1: Initialize with first two values**
```python
for i in range(n):
    for j in range(i + 1, n):
        sa = s[:i+1]      # First substring
        sb = s[i+1:j+1]   # Second substring
        a = int(sa)
        b = int(sb)
        if a == b + 1:    # Check if descending by 1
            if dfs(j + 1, [a, b]):
                return True
```

**Phase 2: DFS to find remaining values**
```python
def dfs(i: int, tmp: List[int]) -> bool:
    if i >= n:
        return True  # Successfully consumed all characters
    
    for j in range(i, n):
        sub = s[i:j+1]
        val = int(sub)
        if val == tmp[-1] - 1:  # Must be exactly 1 less
            tmp.append(val)
            if dfs(j+1, tmp):
                return True
            tmp.pop()  # Backtrack
    return False
```

### Key Insights

1. **Two-stage process:**
   - First, establish the initial two values that differ by 1
   - Then use DFS to find all subsequent values

2. **Why start with two values?**
   - The pattern is determined once we have the first two values
   - We need at least 2 substrings (constraint)

3. **Backtracking:**
   - Try different substring lengths at each position
   - If a path doesn't work, undo the choice (pop from list) and try another

4. **Base case:**
   - When `i >= n`, we've consumed all characters, meaning we found a valid split

### Example Walkthrough: `s = "050043"`

1. Try first substring "0" (value=0) and second substring "5" (value=5): 0 ≠ 5+1, skip
2. Try first substring "0" (value=0) and second substring "50" (value=50): 0 ≠ 50+1, skip
3. Try first substring "05" (value=5) and second substring "0" (value=0): 5 ≠ 0+1, skip
4. Try first substring "05" (value=5) and second substring "00" (value=0): 5 ≠ 0+1, skip
5. Try first substring "05" (value=5) and second substring "004" (value=4): 5 == 4+1 ✓
   - Now DFS from position 5 with tmp=[5, 4]
   - Try "3" (value=3): 3 == 4-1 ✓
   - DFS from position 6 with tmp=[5, 4, 3]
   - i=6 >= n=6, return True!

### Complexity Analysis

**Time Complexity:** O(n³)
- Outer two loops to find first two substrings: O(n²)
- DFS for remaining string: O(n) in worst case
- Each DFS level tries different substring lengths: O(n)
- Overall: O(n³)

**Space Complexity:** O(n)
- Recursion stack depth: O(n) in worst case
- tmp list stores at most n values: O(n)

### Complete Code

```python
class Solution:
    def splitString(self, s: str) -> bool:
        n = len(s)
        
        def dfs(i: int, tmp: List[int]) -> bool:
            if i >= n:
                return True
            
            for j in range(i, n):
                sub = s[i:j+1]
                val = int(sub)
                if val == tmp[-1] - 1:
                    tmp.append(val)
                    if dfs(j+1, tmp):
                        return True
                    tmp.pop()
            return False
        
        # Try all possible ways to split first two substrings
        for i in range(n):
            for j in range(i + 1, n):
                sa = s[:i+1]
                sb = s[i+1:j+1]
                a = int(sa)
                b = int(sb)
                if a == b + 1:
                    if dfs(j + 1, [a, b]):
                        return True
        return False
```

# Tags

`String` `Backtracking` `DFS` `Recursion`

