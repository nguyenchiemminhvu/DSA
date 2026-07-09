## Problem

https://leetcode.com/problems/validate-binary-tree-nodes/description/

Given `n` nodes numbered `0` to `n-1`, and arrays `leftChild` and `rightChild` where `leftChild[i]` and `rightChild[i]` are the left and right children of node `i` (or `-1` if none), return `true` if and only if all nodes form **exactly one valid binary tree**.

---

## Observations

A valid binary tree must satisfy four properties:

1. **Exactly one root** — A root is a node with no parent. If there are zero roots the graph is either empty or fully cyclic; if there are two or more roots the nodes split into separate trees.

2. **Each non-root node has exactly one parent** — In a binary tree every non-root node is the child of exactly one other node. If a node appears as a child of two different nodes it has two parents, which breaks the tree structure.

3. **No self-loops** — A node cannot be its own parent (`leftChild[i] == i` or `rightChild[i] == i`).

4. **All nodes are connected** — BFS/DFS from the root must visit all `n` nodes. If any node is unreachable the graph is a forest (multiple disconnected trees), not a single tree.

These four conditions together are necessary and sufficient for the nodes to form exactly one valid binary tree.

---

## Solution Explanation

```python
class Solution:
    def validateBinaryTreeNodes(self, n: int, left: List[int], right: List[int]) -> bool:
        graph = defaultdict(list)
        parents = defaultdict(list)
        for i in range(n):
            if left[i] != -1:
                parents[left[i]].append(i)
                graph[i].append(left[i])
            if right[i] != -1:
                parents[right[i]].append(i)
                graph[i].append(right[i])
        
        root = -1
        for i in range(n):
            if i not in parents:
                if root == -1:
                    root = i
                else:
                    return False       # more than one root → invalid
            else:
                if len(parents[i]) > 1:
                    return False       # node has two parents → invalid
                if i in parents[i]:
                    return False       # self-loop → invalid
        
        visited = set([root])
        q = deque([root])
        while q:
            cur = q.popleft()
            for adj in graph[cur]:
                if adj not in visited:
                    q.append(adj)
                    visited.add(adj)
        return len(visited) == n       # all nodes reachable → valid
```

**Step 1 — Build parent map and adjacency list.**  
Iterate over every node. For each valid left/right child, record the edge in `graph` (parent → child) and record the parent in `parents` (child → list of parents).

**Step 2 — Validate root and parent counts.**  
- A node `i` with no entry in `parents` is a candidate root. The moment a second candidate is found, return `False`.  
- A node with `len(parents[i]) > 1` has two parents — impossible in a tree.  
- `i in parents[i]` detects a direct self-loop.

**Step 3 — BFS connectivity check.**  
Starting from the single root, perform a BFS over `graph`. After the BFS, if `len(visited) == n` every node was reachable, confirming one connected tree. Otherwise the graph is a forest.

**Time complexity:** O(n) — each edge is processed a constant number of times.  
**Space complexity:** O(n) — for the graph, parent map, and visited set.
