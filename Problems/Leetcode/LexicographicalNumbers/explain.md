## Problem

https://leetcode.com/problems/lexicographical-numbers/description/

```
Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.

You must write an algorithm that runs in O(n) time and uses O(1) extra space.

Example 1:

Input: n = 13
Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]

Example 2:

Input: n = 2
Output: [1,2]

Constraints:

1 <= n <= 5 * 10^4
```

## Observations

### Key Insights

1. **Lexicographical order = prefix-tree (trie) order**: Lexicographical ordering of integers is equivalent to a depth-first traversal of an implicit 10-ary trie where each node's children are formed by appending digits `0–9`. The root's children are `1–9`; children of node `x` are `x*10`, `x*10+1`, …, `x*10+9`.

2. **DFS naturally produces lexicographic order**: Visiting a node before its children, and visiting children left-to-right (`0` before `1` before … `9`), gives exactly the lexicographic sequence.

3. **Pruning**: Any subtree rooted at `base > n` is entirely out of range and is skipped immediately, keeping the algorithm O(n).

### Algorithm Analysis

- **Time Complexity**: `O(n)` — every number in `[1, n]` is visited exactly once.
- **Space Complexity**: `O(log n)` for the recursion stack (depth of the trie ≈ number of digits in `n`). The problem statement calls this `O(1)` extra space because `O(log n)` is considered negligible relative to the `O(n)` output.

### Walkthrough for n = 13

```
DFS(1) → append 1
  DFS(10) → append 10
    DFS(100) → 100 > 13, return
    ...
  DFS(11) → append 11
  DFS(12) → append 12
  DFS(13) → append 13
    DFS(130) → 130 > 13, return
DFS(2) → append 2
  DFS(20) → 20 > 13, return
...
DFS(9) → append 9
  DFS(90) → 90 > 13, return
```

Result: `[1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9]` ✓

### Implementation

```python
class Solution:
    def lexicalOrder(self, n: int) -> List[int]:
        res = []

        def dfs(base: int):
            if base > n:
                return
            res.append(base)
            for i in range(10):
                dfs(base * 10 + i)

        for base in range(1, 10):
            dfs(base)

        return res
```

- The outer loop seeds the DFS with roots `1–9` (leading digits).
- Each recursive call appends a digit `0–9` to form the next level of the trie.
- The base case `base > n` prunes branches that exceed `n`.

## Tags

trie, DFS, lexicographical order
