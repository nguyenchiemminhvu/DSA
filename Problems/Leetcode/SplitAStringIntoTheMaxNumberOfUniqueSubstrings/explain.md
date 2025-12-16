## Problem

https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings/

```
Given a string s, return the maximum number of unique substrings that the given string can be split into.

You can split string s into any list of non-empty substrings, where the concatenation of the substrings 
forms the original string. However, you must split the substrings such that all of them are unique.

A substring is a contiguous sequence of characters within a string.

Example 1:
Input: s = "ababccc"
Output: 5
Explanation: One way to split maximally is ['a', 'b', 'ab', 'c', 'cc']. 
Splitting like ['a', 'b', 'a', 'b', 'c', 'cc'] is not valid as you have 'a' and 'b' multiple times.

Example 2:
Input: s = "aba"
Output: 2
Explanation: One way to split maximally is ['a', 'ba'].

Example 3:
Input: s = "aa"
Output: 1
Explanation: It is impossible to split the string any further.

Constraints:
- 1 <= s.length <= 16
- s contains only lower case English letters.
```

## Observations

1. **Optimization Problem**: We need to find the maximum number of unique substrings, not just any valid split.

2. **Uniqueness Constraint**: Each substring in the final split must be unique - no duplicates allowed.

3. **Complete Coverage**: All substrings must concatenate to form the original string (no characters left out).

4. **Small Input Size**: The constraint `s.length <= 16` is crucial - it suggests an exponential solution is acceptable since we have very limited input size.

5. **Decision at Each Position**: At any position `i`, we can choose to split at different positions (i+1, i+2, ..., n), creating different substrings.

6. **Backtracking Nature**: We need to explore all possible ways to split the string and track which gives us the maximum unique substrings.

7. **State Tracking**: We need to keep track of which substrings we've already used to ensure uniqueness.

## Solution

### Approach: Backtracking with DFS

The solution uses a **depth-first search (DFS) backtracking** approach to explore all possible ways to split the string.

**Key Idea**: At each position in the string, try all possible substring lengths starting from that position. If the substring hasn't been used yet, add it to our set of used substrings and recursively continue from the next position.

**Algorithm Steps**:

1. **Initialization**:
   - `count = [1]`: Store the maximum count (using list to make it mutable in nested function)
   - `visited = set()`: Track currently used substrings in the current path
   - `n = len(s)`: Length of input string

2. **DFS Function**:
   - **Base Case**: If we've processed all characters (`i >= n`), update the maximum count with the size of current split
   - **Recursive Case**: Try all possible substrings starting at position `i`:
     - For each ending position `j` from `i` to `n-1`:
       - Extract substring `s[i:j+1]`
       - If substring not in `visited`:
         - Add it to `visited`
         - Recursively explore from position `j+1`
         - **Backtrack**: Remove substring from `visited` (to try other possibilities)

3. **Return**: The maximum count found

**Why Backtracking?**
- We need to explore ALL possible splits to find the maximum
- At each step, we make a choice (where to split next)
- After exploring one path, we undo our choice (remove from visited) and try another path
- This ensures we explore all combinations without missing any possibility

**Time Complexity**: O(2^n) where n is the length of string
- At each position, we can choose to split or continue
- With backtracking, we explore all possible partitions
- Given the constraint (n ≤ 16), this is acceptable

**Space Complexity**: O(n)
- Recursion depth can go up to n
- `visited` set can store up to n substrings
- Total space is O(n)

**Example Walkthrough** (`s = "aba"`):

```
Start: i=0, visited={}

Try "a" (i=0, j=0):
  visited = {"a"}
  → i=1
    Try "b" (i=1, j=1):
      visited = {"a", "b"}
      → i=2
        Try "a" (i=2, j=2):
          Already in visited, skip
        End of options
      Backtrack: visited = {"a"}
    Try "ba" (i=1, j=2):
      visited = {"a", "ba"}
      → i=3 (end)
        count = max(1, 2) = 2  ✓
      Backtrack: visited = {"a"}
  Backtrack: visited = {}

Try "ab" (i=0, j=1):
  visited = {"ab"}
  → i=2
    Try "a" (i=2, j=2):
      visited = {"ab", "a"}
      → i=3 (end)
        count = max(2, 2) = 2
      Backtrack: visited = {"ab"}
  Backtrack: visited = {}

Try "aba" (i=0, j=2):
  visited = {"aba"}
  → i=3 (end)
    count = max(2, 1) = 2
  Backtrack: visited = {}

Result: 2
```

**Python Implementation**:

```python
class Solution:
    def maxUniqueSplit(self, s: str) -> int:
        count = [1]  # Mutable container to store max count
        n = len(s)
        visited = set()  # Track used substrings in current path
        
        def dfs(i: int) -> None:
            # Base case: reached end of string
            if i >= n:
                count[0] = max(count[0], len(visited))
                return
            
            # Try all possible substrings starting at position i
            for j in range(i, n):
                sub = s[i:j + 1]
                
                # Only proceed if substring is unique
                if sub not in visited:
                    visited.add(sub)      # Choose
                    dfs(j + 1)            # Explore
                    visited.remove(sub)   # Backtrack
        
        dfs(0)
        return count[0]
```

**Key Points**:
- The `count[0]` is updated at each complete split (when we reach the end)
- Backtracking ensures we try all possible combinations
- The `visited` set prevents duplicate substrings in the same split
- Small input constraint (≤16) makes this exponential solution viable

# Tags
#backtracking #dfs #recursion #string #greedy #optimization

