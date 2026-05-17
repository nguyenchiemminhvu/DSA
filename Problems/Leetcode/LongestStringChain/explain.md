## Problem

https://leetcode.com/problems/longest-string-chain/description

You are given an array of words where each word consists of lowercase English letters.

**wordA is a predecessor of wordB** if and only if we can insert exactly one letter anywhere in wordA without changing the order of the other characters to make it equal to wordB.

For example:
- `"abc"` is a predecessor of `"abac"` (insert 'a' between 'b' and 'c')
- `"cba"` is NOT a predecessor of `"bcad"` (would require reordering)

A **word chain** is a sequence of words `[word1, word2, ..., wordk]` with `k >= 1`, where:
- `word1` is a predecessor of `word2`
- `word2` is a predecessor of `word3`
- And so on...

A single word is trivially a word chain with `k == 1`.

**Task:** Return the length of the longest possible word chain with words chosen from the given list.

### Examples

**Example 1:**
```
Input: words = ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: One of the longest word chains is ["a","ba","bda","bdca"]
```

**Example 2:**
```
Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
Output: 5
Explanation: All words form ["xb", "xbc", "cxbc", "pcxbc", "pcxbcf"]
```

**Example 3:**
```
Input: words = ["abcd","dbqca"]
Output: 1
Explanation: Cannot form a chain (ordering is changed)
```

### Constraints
- `1 <= words.length <= 1000`
- `1 <= words[i].length <= 16`
- `words[i]` only consists of lowercase English letters

## Observations

### 1. **Word Length Property**
- If word `A` is a predecessor of word `B`, then `len(B) = len(A) + 1` exactly
- This means we can only form chains by matching words of consecutive lengths
- Sorting by length enables efficient comparison

### 2. **Predecessor Checking (Two-Pointer Technique)**
- To check if `A` is a predecessor of `B`, we need to verify that `A` can be obtained by deleting exactly one character from `B`
- Equivalently, all characters of `A` must appear in `B` in the same order
- Two-pointer approach: advance pointer in `A` when characters match, always advance pointer in `B`
- If we consume all of `A`, then `A` is a predecessor of `B`

### 3. **Optimal Substructure (Dynamic Programming)**
- The problem exhibits optimal substructure: the longest chain ending at word `i` depends on the longest chains ending at its predecessor words
- `dp[i]` = longest chain ending at word at index `i`
- For each word `i`, check all previous words `j` (with `len(words[j]) + 1 == len(words[i])`)
- If `words[j]` is a predecessor of `words[i]`: `dp[i] = max(dp[i], 1 + dp[j])`

### 4. **Efficiency Gain from Sorting**
- After sorting by length, we only need to check earlier words (guaranteed to be shorter or equal length)
- No need for hash maps since we iterate in order—this is more efficient than memoization for this constraint size

## Solution

### Approach: Dynamic Programming with Sorting

```python
class Solution:
    def longestStrChain(self, words: List[str]) -> int:
        n = len(words)
        # Step 1: Sort by word length
        words.sort(key=lambda x: len(x))

        # Step 2: Helper function to check if 'a' is a predecessor of 'b'
        def is_pred(a: str, b: str) -> bool:
            na, nb = len(a), len(b)
            ia, ib = 0, 0
            # Two-pointer: try to match all chars of 'a' in 'b'
            while ia < na and ib < nb:
                if a[ia] == b[ib]:
                    ia += 1
                ib += 1
            # 'a' is predecessor if all its chars were consumed
            return ia == na

        # Step 3: DP where dp[i] = longest chain ending at words[i]
        dp = [1] * n
        res = 1
        
        # For each word at index i
        for i in range(n):
            # Check all previous words
            for j in range(i):
                # Can only form chain if length differs by exactly 1
                if len(words[j]) + 1 == len(words[i]):
                    # If j is predecessor of i, update longest chain
                    if is_pred(words[j], words[i]):
                        dp[i] = max(dp[i], 1 + dp[j])
            # Track the maximum chain length found so far
            res = max(res, dp[i])
        
        return res
```

### Step-by-Step Walkthrough (Example 1)

**Input:** `words = ["a","b","ba","bca","bda","bdca"]`

**After sorting by length:**
```
words = ["a", "b", "ba", "bca", "bda", "bdca"]
indices: 0    1    2     3     4      5
```

**DP Array Evolution:**

| i | word  | Check Predecessors          | dp[i] | Reasoning                       |
|---|-------|-----------------------------|---------|---------------------------------|
| 0 | "a"   | (none)                      | 1     | Single word                     |
| 1 | "b"   | (none)                      | 1     | Single word                     |
| 2 | "ba"  | j=0: "a"→"ba"? ✓ (pred)     | 2     | 1 + dp[0] = 1 + 1 = 2           |
|   |       | j=1: "b"→"ba"? ✓ (pred)     | 2     | max(2, 1 + dp[1] = 2)           |
| 3 | "bca" | j=2: "ba"→"bca"? ✓ (pred)   | 3     | 1 + dp[2] = 1 + 2 = 3           |
| 4 | "bda" | j=2: "ba"→"bda"? ✓ (pred)   | 3     | 1 + dp[2] = 1 + 2 = 3           |
| 5 | "bdca"| j=3: "bca"→"bdca"? ✓ (pred) | 4     | 1 + dp[3] = 1 + 3 = 4           |
|   |       | j=4: "bda"→"bdca"? ✓ (pred) | 4     | max(4, 1 + dp[4] = 4)           |

**Answer:** 4 (Chain: "a" → "ba" → "bda" → "bdca")

### Predecessor Check Detail (is_pred)

For `is_pred("ba", "bdca")`:
```
a = "ba"   (na = 2, ia = 0)
b = "bdca" (nb = 4, ib = 0)

Iteration:
  ib=0: b[0]='b', a[0]='b'? ✓ → ia=1, ib=1
  ib=1: b[1]='d', a[1]='a'? ✗ → ib=2
  ib=2: b[2]='c', a[1]='a'? ✗ → ib=3
  ib=3: b[3]='a', a[1]='a'? ✓ → ia=2, ib=4

Result: ia==na (2==2) → True ✓
```

### Complexity Analysis

- **Time Complexity:** $O(n \log n + n^2 \cdot m)$
  - Sorting: $O(n \log n)$
  - DP loop: $O(n^2)$ pairs checked
  - `is_pred` for each pair: $O(m)$ where $m \leq 16$ is max word length
  - Total: $O(n \log n + n^2 \cdot 16) = O(n^2)$ practically

- **Space Complexity:** $O(n)$ for the DP array (sorting is in-place)

### Alternative: Memoized Recursion (Commented in Original)

The original solution also includes a recursive memoization approach that works similarly but requires tracking previous indices explicitly. The iterative DP approach is cleaner and more efficient for this problem size.

# Tags

- Dynamic Programming
- Two-Pointer Technique
- Sorting
- Optimal Substructure

