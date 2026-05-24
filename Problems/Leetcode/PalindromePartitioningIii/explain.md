## Problem

https://leetcode.com/problems/palindrome-partitioning-iii/description

Given a string `s` containing lowercase English letters and an integer `k`, you need to:
1. Change some characters of `s` to other lowercase English letters
2. Divide the modified string into exactly `k` non-empty disjoint substrings
3. Ensure each substring is a palindrome

**Goal:** Return the minimum number of character changes needed.

**Examples:**
- Input: `s = "abc"`, `k = 2` → Output: `1` (split into "ab" → "aa", "c")
- Input: `s = "aabbc"`, `k = 3` → Output: `0` (split into "aa", "bb", "c")
- Input: `s = "leetcode"`, `k = 8` → Output: `0` (each char is a palindrome)

**Constraints:** `1 <= k <= s.length <= 100`, `s` contains lowercase letters only

## Observations

1. **Making a substring palindromic:** To convert any substring `s[l:r+1]` into a palindrome, we only need to compare characters from both ends and move inward. For each mismatch, change one character (we can change either one). This costs $\lceil(r - l + 1) / 2\rceil$ mismatches at most.

2. **Partition structure:** We must split the string into exactly `k` parts. This is a partitioning problem where:
   - We have a choice of where to place each partition boundary
   - The order of partitions matters (left-to-right)
   - We want to minimize total changes across all parts

3. **DP formulation:** Define `F(i, cnt)` = minimum changes to partition `s[i:]` into exactly `cnt` palindromic substrings.
   - Base case: If `i >= n`, we've consumed the entire string
   - When `cnt == 1`, the remaining substring must be one palindrome
   - Recurrence: Try all possible positions for the next partition, choosing the split that gives minimum cost

4. **Time complexity:** 
   - Computing `cost(l, r)` takes $O(n)$ for each pair → $O(n^2)$ total preprocessing
   - DP has $O(n \cdot k)$ states, each state tries $O(n)$ transitions
   - Total: $O(n^2 \cdot k)$

## Solution

### Approach: Top-Down Dynamic Programming with Memoization

```python
class Solution:
    def palindromePartition(self, s: str, k: int) -> int:
        n = len(s)
        INF = float('inf')

        def cost(l: int, r: int) -> int:
            """Calculate minimum changes to make s[l:r+1] a palindrome"""
            changes = 0
            while l <= r:
                if s[l] != s[r]:
                    changes += 1
                l += 1
                r -= 1
            return changes

        mem = {}
        def F(i: int, cnt: int) -> int:
            """Minimum changes to partition s[i:] into cnt palindromes"""
            # Base case: reached end of string
            if i >= n:
                return 0
            
            # Only one partition left - entire remaining string must be palindrome
            if cnt == 1:
                return cost(i, n - 1)
            
            # Check memoization
            if (i, cnt) in mem:
                return mem[(i, cnt)]
            
            # Try all possible positions for next partition boundary
            res = INF
            for j in range(n - 1, i, -1):
                # Make s[i:j] a palindrome, then solve for s[j:] with cnt-1 parts
                res = min(
                    res,
                    cost(i, j - 1) + F(j, cnt - 1)
                )
            
            mem[(i, cnt)] = res
            return res

        return F(0, k)
```

### Key Components

#### 1. **`cost(l, r)` Helper Function**
Computes the minimum character changes needed to make substring `s[l:r+1]` a palindrome.

**Algorithm:**
- Use two pointers: one at left (`l`) and one at right (`r`)
- Move them toward center, comparing characters at each position
- If they don't match, increment change count (we change one of them)
- When pointers meet or cross, we have the answer

**Example:** `cost(0, 2)` for `"abc"`:
```
l=0, r=2: s[0]='a' != s[2]='c' → changes=1, move pointers
l=1, r=1: s[1]='b' == s[1]='b' → no change
Result: 1 (change either 'a'→'c' or 'c'→'a' to get "aca")
```

#### 2. **`F(i, cnt)` Recursive Function**
Solves the partitioning problem using memoized recursion.

**Parameters:**
- `i`: starting index in string `s`
- `cnt`: number of palindromic parts needed

**Logic:**
1. **Base case:** `i >= n` (end of string reached) → 0 changes needed
2. **Single partition:** `cnt == 1` → entire remaining substring must be palindrome, return `cost(i, n-1)`
3. **Multiple partitions:** Try every possible position `j` for the next partition boundary:
   - First part: `s[i:j]` (costs `cost(i, j-1)` changes)
   - Remaining: `s[j:]` (costs `F(j, cnt-1)` changes)
   - Take minimum across all choices

**Example trace** for `s = "aabbc"`, `k = 3`:
```
F(0, 3):
  Try j=1: cost(0,0)=0 (s[0:1]="a") + F(1,2)
  Try j=2: cost(0,1)=0 (s[0:2]="aa") + F(2,2)  ← Optimal path
  Try j=3: cost(0,2)=0 (s[0:3]="aab"→need changes) + F(3,2)
  ...

F(2, 2):
  Try j=3: cost(2,2)=0 (s[2:3]="b") + F(3,1)
  Try j=4: cost(2,3)=0 (s[2:4]="bb") + F(4,1)  ← Optimal
  
F(4, 1):
  cnt==1: cost(4,4)=0 (s[4:5]="c")

Total: 0 + 0 + 0 = 0 ✓
```

### Time & Space Complexity

- **Time:** $O(n^2 \cdot k)$ 
  - $O(n \cdot k)$ DP states
  - Each state iterates through $O(n)$ partition positions
  - `cost()` calls take $O(n)$ per call, but amortized is acceptable given problem constraints ($n \leq 100$)

- **Space:** $O(n \cdot k)$ for memoization dictionary + $O(n)$ recursion depth

### Why This Works

1. **Optimality:** By trying all possible partition positions and taking the minimum, we explore all valid partitioning strategies
2. **Overlapping subproblems:** Same `(i, cnt)` pairs may arise from different paths → memoization avoids recomputation
3. **Greedy within DP:** While we can't greedily choose partitions (a locally optimal choice might block better partitions later), DP explores all possibilities systematically

# Tags

