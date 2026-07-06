## Problem

https://leetcode.com/problems/minimum-height-trees/description/

Given an undirected tree of `n` nodes (labelled `0` to `n-1`) and `n-1` edges, find all nodes that, when chosen as root, produce a tree of **minimum height**. The height of a rooted tree is the number of edges on the longest downward path from the root to any leaf.

There are at most **2** such roots. Return them in any order.

---

## Observations

1. **At most 2 MHT roots exist.**  
   The optimal root(s) lie at the center of the tree's longest path (the *diameter*). A path has either 1 or 2 midpoints, so there can never be more than 2 answers.

2. **The problem reduces to finding the tree's centroid.**  
   Rooting at the centroid minimizes the longest downward path because it balances the distances to the farthest leaves in every direction.

3. **Leaves are never optimal roots** (for `n > 2`).  
   A leaf is an endpoint of the diameter, so rooting there produces the maximum possible height. The center of the diameter is always strictly better.

4. **Iterative leaf pruning converges to the centroid.**  
   If we repeatedly remove all current leaves, the remaining nodes shrink toward the center. When only 1 or 2 nodes remain, those are the MHT roots. This is equivalent to peeling an onion layer by layer from the outside in.

---

## Solution Explanation

The algorithm is a **BFS-based topological trim** (analogous to Kahn's algorithm for topological sort, but on an undirected tree).

### Steps

1. **Base case**: if `n ≤ 2`, every node is a valid root — return `[0, ..., n-1]`.

2. **Build adjacency sets** (`defaultdict(set)`) for the undirected graph.

3. **Initialize the queue with all leaves** — nodes whose degree (`len(graph[i])`) equals 1.

4. **Trim leaves in rounds** until `node_count ≤ 2`:
   - Process every current leaf in the queue.
   - For each leaf `cur`, decrement `node_count` and remove it from its sole neighbor's adjacency set.
   - If that neighbor now has degree 1, it becomes a new leaf — enqueue it for the next round.

5. **Whatever remains in the queue** (1 or 2 nodes) are the MHT roots.

### Why it works

Each round of trimming removes one "shell" of leaves — the outermost layer of the tree. After enough rounds the peeling stops at the innermost node(s). Those innermost nodes are equidistant (or as close as possible) from all leaves in every direction, which is exactly the definition of the centroid and the optimal root(s).

### Complexity

| | |
|---|---|
| Time  | O(n) — every node and edge is processed at most once |
| Space | O(n) — adjacency sets + queue |

---

## Code

```python
from collections import defaultdict, deque
from typing import List

class Solution:
    def findMinHeightTrees(self, n: int, edges: List[List[int]]) -> List[int]:
        if n <= 2:
            return [i for i in range(n)]

        graph = defaultdict(set)
        for u, v in edges:
            graph[u].add(v)
            graph[v].add(u)

        q = deque([i for i in range(n) if len(graph[i]) == 1])

        node_count = n
        while node_count > 2:
            z = len(q)
            for _ in range(z):
                cur = q.popleft()
                node_count -= 1

                adj = graph[cur].pop()   # leaf has exactly one neighbor
                graph[adj].remove(cur)

                if len(graph[adj]) == 1:
                    q.append(adj)

        return list(q)
```

### Trace — Example 2 (`n=6, edges=[[3,0],[3,1],[3,2],[3,4],[5,4]]`)

```
Initial graph:
  0: {3}
  1: {3}
  2: {3}
  3: {0,1,2,4}
  4: {3,5}
  5: {4}

Leaves (degree 1): [0, 1, 2, 5]   node_count = 6

Round 1 — trim 0, 1, 2, 5:
  Remove 0 → graph[3] = {1,2,4}   (degree 3, not a leaf)
  Remove 1 → graph[3] = {2,4}     (degree 2, not a leaf)
  Remove 2 → graph[3] = {4}       (degree 1 → enqueue 3)
  Remove 5 → graph[4] = {3}       (degree 1 → enqueue 4)
  node_count = 2  →  stop

Queue = [3, 4]  →  return [3, 4]  ✓
```
