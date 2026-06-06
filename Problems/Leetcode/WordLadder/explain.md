## Problem

https://leetcode.com/problems/word-ladder/description/

Given two words `beginWord` and `endWord`, and a dictionary `wordList`, return the **number of words** in the **shortest transformation sequence** from `beginWord` to `endWord`, or `0` if no such sequence exists.

A transformation sequence is valid when:
- Every adjacent pair of words differs by exactly **one letter**.
- Every intermediate word must exist in `wordList`.
- The last word equals `endWord`.

**Example 1:**
```
Input:  beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Reason: "hit" -> "hot" -> "dot" -> "dog" -> "cog"  (5 words)
```

**Example 2:**
```
Input:  beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Reason: "cog" is not in wordList, so no valid sequence exists.
```

**Constraints:**
- `1 <= beginWord.length <= 10`
- All words have the same length.
- `1 <= wordList.length <= 5000`
- All words consist of lowercase English letters.
- `beginWord != endWord`, all words in `wordList` are unique.

---

## Solution

### Intuition

The problem asks for the **shortest** path between two nodes in an implicit graph where:
- Each word is a node.
- Two words are connected by an edge if they differ by exactly one letter.

Shortest path in an unweighted graph → **BFS (Breadth-First Search)**.

BFS guarantees that the first time we reach `endWord`, we have taken the minimum number of steps.

### Approach

1. **Early exits:** If `endWord` is not in `wordList`, return `0` immediately — no solution can exist.
2. **BFS setup:** Use a queue of `(currentWord, steps)` starting from `(beginWord, 1)`. A `visited` set prevents revisiting words.
3. **Neighbor discovery:** For each word dequeued, scan every word in the bank. If it differs by exactly one character and hasn't been visited, enqueue it with `steps + 1`.
4. **Termination:** Return `steps` the moment we dequeue `endWord`. If the queue empties without finding it, return `0`.

### Complexity

| | Value |
|---|---|
| Time | O(N · L²) where N = number of words, L = word length |
| Space | O(N) for the visited set and queue |

> The `count_diff` helper is O(L), called O(N) times per BFS level, giving O(N · L) per level and O(N · L²) overall (at most L levels in the worst case; more precisely bounded by N levels).

### Code

```python
from collections import deque
from typing import List

class Solution:
    def ladderLength(self, start: str, end: str, bank: List[str]) -> int:
        if start == end:
            return 0
        if end not in bank:
            return 0

        def count_diff(a: str, b: str) -> int:
            count = 0
            for i in range(len(a)):
                if a[i] != b[i]:
                    count += 1
            return count

        bank = set(bank)          # O(1) lookups for visited check
        q = deque([(start, 1)])   # (word, sequence length so far)
        visited = set([start])

        while q:
            s, step = q.popleft()
            if s == end:
                return step

            for word in bank:
                if word not in visited and count_diff(s, word) == 1:
                    visited.add(word)
                    q.append((word, step + 1))

        return 0
```

### Walkthrough — Example 1

```
beginWord = "hit", endWord = "cog"
wordList  = ["hot","dot","dog","lot","log","cog"]

Queue (word, step):
  ("hit", 1)  → neighbors: "hot"  (differs at index 0: h→h, i→o, t→t  ✗ ... h→h at 0 same, i≠o at 1 ✓, t=t same → 1 diff ✓)
  ("hot", 2)  → neighbors: "dot", "lot"
  ("dot", 3)  → neighbors: "dog", "lot"
  ("lot", 3)  → neighbors: "log"
  ("dog", 4)  → neighbors: "cog"  ← endWord found!
  return 5
```

### Key Design Decisions

- **`bank` as a `set`:** Iteration is still O(N), but `word not in visited` remains O(1). The main benefit is that `end not in bank` is O(1) at the start.
- **Mark visited on enqueue, not on dequeue:** Prevents the same word from being added to the queue multiple times, which is critical for correctness and performance.
- **Scanning all bank words vs. generating mutations:** An alternative O(L · 26) neighbor generation (swap each position with 'a'–'z' and check membership) is faster for large N but this linear scan is simpler and acceptable within constraints.
