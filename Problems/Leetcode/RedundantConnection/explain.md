## Problem

https://leetcode.com/problems/redundant-connection/description/

In this problem, a **tree** is an undirected graph that is connected and has no cycles.

You are given a graph that started as a tree with `n` nodes labeled from `1` to `n`, with one additional edge added. The added edge has two different vertices chosen from `1` to `n`, and was not an edge that already existed. The graph is represented as an array `edges` of length `n` where `edges[i] = [ai, bi]` indicates that there is an edge between nodes `ai` and `bi` in the graph.

Return an edge that can be removed so that the resulting graph is a tree of `n` nodes. If there are multiple answers, return the answer that occurs last in the input.

**Example 1:**
```
Input: edges = [[1,2],[1,3],[2,3]]
Output: [2,3]
```
**Example 2:**
```
Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
Output: [1,4]
```

**Constraints:**
- `n == edges.length`
- `3 <= n <= 1000`
- `edges[i].length == 2`
- `1 <= ai < bi <= edges.length`
- `ai != bi`
- There are no repeated edges.
- The given graph is connected.

## Observations

- A tree with `n` nodes has exactly `n - 1` edges. The input provides exactly `n` edges — one more than needed — so there is **exactly one redundant edge**.
- Adding one extra edge to a tree creates **exactly one cycle**. The redundant edge is any edge inside that cycle.
- If we build the graph by adding edges one by one, the first edge whose two endpoints are already **in the same connected component** is the one that creates the cycle — it is the redundant edge.
- This is a textbook application of **Union-Find (Disjoint Set Union)**:
  - For each edge `(u, v)`, attempt to `union(u, v)`.
  - If `u` and `v` already share the same root (i.e., `find(u) == find(v)`), they are already connected. Adding this edge would form a cycle → record it as the answer.
  - If the union succeeds, the edge is valid and the two components are merged.
- Because we process edges in order and overwrite the result on each redundant edge found, we naturally return the **last** redundant edge in the input (though by the problem's guarantee there is exactly one).
- **Union by rank** keeps the tree flat, ensuring near-constant time per operation.
- **Path compression** in `find` further amortizes the cost across all queries.

## Solution

```python
class DSU:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [0] * size

    def find(self, i):
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])  # path compression
        return self.parent[i]

    def union(self, i, j):
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i == root_j:
            return False   # already connected → this edge is redundant

        # union by rank: attach smaller tree under larger tree
        if self.rank[root_i] < self.rank[root_j]:
            self.parent[root_i] = root_j
        elif self.rank[root_i] > self.rank[root_j]:
            self.parent[root_j] = root_i
        else:
            self.parent[root_j] = root_i
            self.rank[root_i] += 1
        return True

class Solution:
    def findRedundantConnection(self, edges: List[List[int]]) -> List[int]:
        n = max(max(u, v) for u, v in edges) + 1
        dsu = DSU(n)
        res = [-1, -1]
        for u, v in edges:
            if not dsu.union(u, v):
                res = [u, v]   # keep updating so we return the last one
        return res
```

**Step-by-step walkthrough (Example 1: `edges = [[1,2],[1,3],[2,3]]`):**

| Step | Edge  | `find(u)` | `find(v)` | Same root? | Action              |
|------|-------|-----------|-----------|------------|---------------------|
| 1    | [1,2] | 1         | 2         | No         | Union → `parent[2]=1` |
| 2    | [1,3] | 1         | 3         | No         | Union → `parent[3]=1` |
| 3    | [2,3] | 1         | 1         | **Yes**    | Redundant → `res=[2,3]` |

Output: `[2,3]` ✓

**Complexity:**
- Time: $O(n \cdot \alpha(n))$ where $\alpha$ is the inverse Ackermann function — effectively $O(n)$
- Space: $O(n)$ for the `parent` and `rank` arrays

## Tags

`Graph` `Union-Find` `Cycle Detection`
