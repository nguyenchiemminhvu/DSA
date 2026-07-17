## Problem

https://leetcode.com/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph/description/

Given `n` nodes (0-indexed) and directed edges, return `answer` where `answer[i]` is the sorted list of all ancestors of node `i`. Node `u` is an ancestor of `v` if there exists a directed path from `u` to `v`.

---

## Observations

1. **Ancestor = transitive predecessor.** The ancestors of node `v` are its direct parents plus all of their ancestors — a naturally recursive definition.

2. **DAG guarantee.** No cycles, so DFS terminates and there are no conflicting ancestor claims.

3. **Reversed-graph trick.** If we reverse every edge, then following edges from node `v` leads to its direct parents in the original graph. A full DFS from `v` in the reversed graph yields all ancestors of `v`.

4. **Memoization opportunity.** The ancestor sets are shared across nodes:  
   `ancestors(v) = ancestors(parent₁) ∪ ancestors(parent₂) ∪ ... ∪ {parent₁, parent₂, ...}`  
   Caching `dfs(node)` avoids redundant recomputation.

5. **Entry points.** In a DAG every node can reach at least one **sink** (a node with no outgoing edges). By starting DFS from every sink we guarantee every node is eventually visited. Sinks are exactly the nodes with `in_degree == 0` under the coding convention used here (see below).

---

## Solution walkthrough

```python
class Solution:
    def getAncestors(self, n: int, edges: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        in_degree = [0] * n
        for u, v in edges:
            graph[v].append(u)   # reversed edge: v → u
            in_degree[u] += 1    # count outgoing edges of u in original

        parents = [[] for _ in range(n)]

        from functools import lru_cache
        @lru_cache(None)
        def dfs(cur: int) -> List[int]:
            arrs = set()
            for adj in graph[cur]:          # adj is a direct parent of cur
                arr = dfs(adj)              # all ancestors of adj (+ adj itself)
                arrs.update(arr)
            parents[cur] = sorted(list(arrs))   # ancestors of cur (not including cur)
            arrs.add(cur)                        # include cur for callers
            return list(arrs)

        for i in range(n):
            if in_degree[i] == 0:
                dfs(i)

        return parents
```

### Step-by-step

**Graph construction**

For each original edge `u → v`:
- Add a reversed edge `v → u` into `graph[v]`. Now `graph[v]` holds all direct parents of `v`.
- Increment `in_degree[u]`. Here `in_degree[u]` counts the number of **outgoing** edges of `u` in the original graph, which equals the number of **incoming** edges of `u` in the reversed graph.

Nodes where `in_degree[i] == 0` have no outgoing edges in the original — they are **sinks** and therefore **sources** in the reversed graph.

**DFS with memoization**

`dfs(cur)` returns the set of ancestors of `cur` **plus `cur` itself** (so a caller can include `cur` in its own ancestor set).

- For every direct parent `adj` of `cur` (i.e., every node in `graph[cur]`), call `dfs(adj)` to get `adj`'s full ancestor chain including `adj`.
- Union all those sets → this is the complete ancestor set of `cur`.
- Store the **sorted** ancestor list in `parents[cur]` before adding `cur` to the set.
- Add `cur` to the set and return it for callers higher up the chain.

`@lru_cache(None)` memoizes results keyed on `cur`, so each node's ancestor set is computed at most once even when multiple paths converge on it.

**Starting the traversal**

Only sink nodes (those with `in_degree[i] == 0`) are seeded explicitly. Because every node in a finite DAG has at least one path to some sink, the recursive calls from each sink will eventually reach and populate every node's `parents` entry.

### Complexity

| | |
|---|---|
| **Time** | $O(n^2)$ — each node's ancestor set can be $O(n)$ in the worst case, and we process $O(n)$ nodes |
| **Space** | $O(n^2)$ — to store all ancestor lists |
