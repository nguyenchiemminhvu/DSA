## Problem

https://leetcode.com/problems/longest-word-in-dictionary/description/

Given an array of strings `words` representing an English Dictionary, return the longest word in `words` that can be built one character at a time by other words in `words`.

- If there is more than one possible answer, return the longest word with the smallest lexicographical order.
- If there is no answer, return the empty string.
- The word must be built **left to right** — each prefix of the word must also exist in `words`.

**Example 1:**
```
Input:  words = ["w","wo","wor","worl","world"]
Output: "world"
```

**Example 2:**
```
Input:  words = ["a","banana","app","appl","ap","apply","apple"]
Output: "apple"
Explanation: Both "apply" and "apple" can be built, but "apple" < "apply" lexicographically.
```

**Constraints:**
- `1 <= words.length <= 1000`
- `1 <= words[i].length <= 30`
- `words[i]` consists of lowercase English letters.

---

## Observations

1. **Prefix condition.** A word `w` of length `n` is valid if and only if every prefix `w[0..1]`, `w[0..2]`, …, `w[0..n]` is present in `words`. This is exactly the "every prefix exists" property.

2. **Trie is a natural fit.** A Trie stores words by shared prefixes. After inserting all words, a node that is marked `completed` means the corresponding prefix exists as a complete word in the dictionary. So a path from the root where **every node along the path is `completed`** represents a valid buildable word.

3. **DFS pruning.** During DFS traversal of the Trie, if the current node is **not** `completed`, the word represented so far cannot be extended into a valid answer — we prune the entire subtree. This avoids redundant work.

4. **Tie-breaking.** Among all valid words of the same maximum length, we want the lexicographically smallest. Since `dict.keys()` in Python preserves insertion order (Python 3.7+) but is not sorted, we must compare candidates explicitly when lengths are equal.

---

## Solution Explanation

### Data Structures

```
TrieNode:
    completed  — True if the path to this node forms a word in `words`
    children   — map from character → TrieNode
```

The `Trie.root` is pre-marked `completed = True` so that the DFS starts without immediately pruning.

### Algorithm

**Step 1 — Build the Trie.**  
Insert every word from `words` into the Trie, marking the terminal node of each word as `completed`.

**Step 2 — DFS with pruning.**  
Traverse the Trie depth-first. At each node:
- If `completed` is `False`, **stop** — this prefix was never a full word in `words`, so no descendant can be a valid answer.
- Otherwise, check if the current path length beats (or ties with better lex order) the current best.
- Recurse into all children.

**Step 3 — Return the best word found.**

### Walkthrough — Example 2

```
words = ["a","banana","app","appl","ap","apply","apple"]
```

After insertion, the Trie has `completed = True` on nodes for:
`a`, `ap`, `app`, `appl`, `apple`, `apply`, `banana`

DFS from root → `a` (✓) → `p` (✓, "ap") → `p` (✓, "app") → `l` (✓, "appl") → `e` (✓, "apple", len=5) → `y` (✓, "apply", len=5, but "apple" < "apply" so keep "apple")

The path through `b` ("banana") gets pruned at `b`'s child `a` because "ba" is not in words.

**Result: `"apple"`**

### Complexity

| | |
|---|---|
| Time  | $O(N \cdot L)$ — insert $N$ words of max length $L$; DFS visits each Trie node at most once |
| Space | $O(N \cdot L \cdot \Sigma)$ — Trie storage, where $\Sigma = 26$ |

### Code

```python
class TrieNode:
    def __init__(self):
        self.completed = False
        self.children = {}

class Trie:
    def __init__(self):
        self.root = TrieNode()
        self.root.completed = True  # sentinel: empty prefix always "exists"

    def insert(self, word):
        p = self.root
        for c in word:
            if c not in p.children:
                p.children[c] = TrieNode()
            p = p.children[c]
        p.completed = True

    def get_longest_word(self):
        max_len = 0
        max_word = ''

        def dfs(p, length, temp):
            nonlocal max_len, max_word
            if not p.completed:      # prune: prefix not in words
                return

            if length > 0:           # skip the empty root
                if length > max_len:
                    max_len = length
                    max_word = ''.join(temp)
                elif length == max_len:
                    candidate = ''.join(temp)
                    if candidate < max_word:   # prefer lex smaller
                        max_word = candidate

            for c, child in p.children.items():
                dfs(child, length + 1, temp + [c])

        dfs(self.root, 0, [])
        return max_word

class Solution:
    def longestWord(self, words: List[str]) -> str:
        trie = Trie()
        for word in words:
            trie.insert(word)
        return trie.get_longest_word()
```

> **Note on the original code:** The condition `if max_len <= length` also processes the root (length 0) unnecessarily. Using `length > 0` as a guard, and checking `length > max_len` before `length == max_len`, makes the intent clearer and avoids one redundant comparison path.
