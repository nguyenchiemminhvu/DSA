## Problem

https://leetcode.com/problems/word-break-ii/description/

# Word Break II (LeetCode 140)

## Problem

https://leetcode.com/problems/word-break-ii/description/

Given a string `s` and a dictionary of strings `wordDict`, add spaces in `s` to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.

**Key constraints:**
- The same word in the dictionary may be reused multiple times
- 1 ≤ s.length ≤ 20
- 1 ≤ wordDict.length ≤ 1000
- 1 ≤ wordDict[i].length ≤ 10
- All strings in wordDict are unique and consist of lowercase English letters

**Examples:**

| Example | Input | Output |
|---------|-------|--------|
| 1 | s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"] | ["cats and dog","cat sand dog"] |
| 2 | s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"] | ["pine apple pen apple","pineapple pen apple","pine applepen apple"] |
| 3 | s = "catsandog", wordDict = ["cats","dog","sand","and","cat"] | [] |

---

## Observations

### 1. **Combinatorial Nature**
- This is a backtracking problem where we need to find ALL valid combinations
- At each position, we try every word in the dictionary that matches at that position
- If a word matches, we recursively try to segment the remaining string

### 2. **Greedy Won't Work**
- Simply taking the longest matching word at each step won't find all solutions
- Example: "catsanddog" with ["cat","cats","and","sand","dog"]
  - If we greedily take "cats" first, we get one solution
  - If we take "cat" first, we get another solution
  - We need to explore both paths

### 3. **Early Termination Potential**
- If we check that the remaining substring CAN be segmented before exploring, we can prune branches early
- This is a two-phase approach: first check feasibility (DP), then generate solutions (Backtracking)

### 4. **Constraint Advantage**
- The string length is small (≤ 20), making brute-force backtracking feasible
- Output size is bounded by 10^5, so we won't have explosion in memory

### 5. **Backtracking Strategy**
- Start at index 0
- At each position i, try every word in the dictionary
- If the word matches the substring starting at i, add it to the current path and recurse
- When we reach the end of the string, add the current path to results
- Backtrack by removing the word from the current path

---

## Solution Approach: Backtracking with DFS

### Algorithm Explanation

```python
class Solution:
    def wordBreak(self, s: str, words: List[str]) -> List[str]:
        n = len(s)
        res = []
        
        def dfs(i: int, temp: List[str]):
            # Base case: if index exceeds string length, invalid state
            if i > n:
                return
            
            # Base case: reached end of string, add the sentence to results
            if i == n:
                res.append(" ".join(temp))
                return
            
            # Try each word in the dictionary
            for word in words:
                nw = len(word)
                # Check if word matches at current position
                if i + nw <= n and s[i:i + nw] == word:
                    # Add word to current path
                    temp.append(word)
                    # Recursively process remaining string
                    dfs(i + nw, temp)
                    # Backtrack: remove word from current path
                    temp.pop()
        
        dfs(0, [])
        return res
```

### Step-by-Step Execution Example

**Input:** s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]

```
dfs(0, [])
├─ Try "cat": s[0:3] = "cat" ✓
│  ├─ dfs(3, ["cat"])
│  │  ├─ Try "and": s[3:6] = "and" ✓
│  │  │  ├─ dfs(6, ["cat","and"])
│  │  │  │  ├─ Try "dog": s[6:9] = "dog" ✓
│  │  │  │  │  ├─ dfs(9, ["cat","and","dog"])
│  │  │  │  │  │  └─ i==n, add "cat and dog" ✓
│  │  │  │  ├─ Try "sand": s[6:10] > n ✗
│  │  │  │  └─ ...continue
│  │  │  └─ backtrack
│  │  └─ Try "sand": s[3:7] = "sand" ✓
│  │     ├─ dfs(7, ["cat","sand"])
│  │     │  └─ No valid matches lead to n
│  │     └─ backtrack
│  └─ ...continue
│
└─ Try "cats": s[0:4] = "cats" ✓
   ├─ dfs(4, ["cats"])
   │  ├─ Try "and": s[4:7] = "and" ✓
   │  │  ├─ dfs(7, ["cats","and"])
   │  │  │  ├─ Try "dog": s[7:10] = "dog" ✓
   │  │  │  │  ├─ dfs(10, ["cats","and","dog"])
   │  │  │  │  │  └─ i==n, add "cats and dog" ✓
   │  │  │  └─ ...continue
   │  │  └─ backtrack
   │  └─ ...continue
   └─ ...
```

### Complexity Analysis

| Metric | Value | Explanation |
|--------|-------|-------------|
| **Time Complexity** | O(N × 2^N) | In worst case, every substring is a valid word, creating 2^N combinations. For each, we join strings (O(N)). |
| **Space Complexity** | O(N) | Recursion depth can be at most N, and we store temporary words. Output space not counted (as per LeetCode convention). |

**More precisely:** The time complexity depends on the dictionary structure, but worst case is bounded by the constraint that output size ≤ 10^5.

### Key Points in Implementation

1. **Boundary Check:** `i + nw <= n` ensures we don't access beyond string length
2. **String Matching:** `s[i:i + nw] == word` checks if the word matches at position i
3. **Backtracking:** `temp.pop()` undoes the choice to explore other paths
4. **Base Case:** When `i == n`, we've successfully segmented the entire string
5. **Early Exit:** `if i > n: return` handles impossible states (shouldn't occur with proper boundary check)

### Potential Optimization: Memoization + Backtracking

For potentially large inputs, we can first use DP to determine if each position can reach the end:

```python
class Solution:
    def wordBreak(self, s: str, words: List[str]) -> List[str]:
        n = len(s)
        word_set = set(words)
        
        # DP: can we reach the end from each position?
        can_reach = [False] * (n + 1)
        can_reach[n] = True
        
        for i in range(n - 1, -1, -1):
            for word in words:
                nw = len(word)
                if i + nw <= n and s[i:i + nw] == word and can_reach[i + nw]:
                    can_reach[i] = True
                    break
        
        # If cannot reach end from start, return early
        if not can_reach[0]:
            return []
        
        res = []
        def dfs(i: int, temp: List[str]):
            if i == n:
                res.append(" ".join(temp))
                return
            
            for word in words:
                nw = len(word)
                if i + nw <= n and s[i:i + nw] == word and can_reach[i + nw]:
                    temp.append(word)
                    dfs(i + nw, temp)
                    temp.pop()
        
        dfs(0, [])
        return res
```

This optimization prunes branches early and significantly improves performance on unsolvable inputs.

---

## Tags

- **Backtracking**
- **Dynamic Programming** (for optimization)
- **DFS (Depth-First Search)**
- **String Segmentation**
- **Recursion**