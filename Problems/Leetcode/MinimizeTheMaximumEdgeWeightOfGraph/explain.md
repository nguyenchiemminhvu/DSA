## Problem

https://leetcode.com/problems/minimize-the-maximum-edge-weight-of-graph/description/

Given a directed weighted graph of `n` nodes and a `threshold`, remove some edges so that:
1. Node 0 is reachable from **all** other nodes.
2. Each node has **at most** `threshold` outgoing edges.
3. The **maximum** edge weight in the remaining graph is **minimized**.

Return the minimum possible maximum edge weight, or `-1` if impossible.

---

## Observations

**1. The answer space is monotonic (binary search applies).**

If it's possible to satisfy all conditions with maximum edge weight `W`, then it's also possible with any `W' > W` (just keep the same edges). Conversely, if `W` is infeasible, all smaller values are also infeasible. This monotonicity means we can binary search on the answer over the range `[1, max_weight]`.

**2. Checking feasibility = checking reachability to node 0.**

For a fixed bound `W`, keep only edges with weight `≤ W`. The question becomes: can every node reach node 0 in this subgraph?

**3. The threshold constraint is automatically satisfiable when reachability holds.**

The constraints guarantee `threshold ≥ 1`. If all nodes can reach node 0, we can always build a **spanning arborescence** — a directed spanning tree where every non-root node has exactly **one** outgoing edge pointing toward node 0 (directly or transitively). This uses exactly 1 outgoing edge per non-root node, which satisfies `threshold ≥ 1`. Therefore, we never need to explicitly check the threshold; reachability alone determines feasibility.

**4. Checking reachability efficiently via reversed BFS.**

To check whether all nodes can reach node 0, reverse every edge and run BFS/DFS from node 0 on the reversed graph. If node 0 can reach all `n` nodes in the reversed graph, then all nodes can reach node 0 in the original graph.

---

## Solution Explanation

```python
class Solution:
    def minMaxWeight(self, n: int, edges: List[List[int]], threshold: int) -> int:
        from collections import defaultdict, deque

        # Build reversed graph: original edge u->v becomes v->u
        graph = defaultdict(list)
        for u, v, w in edges:
            graph[v].append((u, w))

        def can(bound):
            # BFS from node 0 on reversed graph, using only edges with weight <= bound
            # If all n nodes are visited, every node can reach 0 in original graph
            visited = [False] * n
            q = deque([0])
            visited[0] = True
            count = 1

            while q:
                node = q.popleft()
                for nei, w in graph[node]:
                    if w <= bound and not visited[nei]:
                        visited[nei] = True
                        count += 1
                        if count == n:
                            return True
                        q.append(nei)

            return count == n

        low, high = 1, max(w for _, _, w in edges)
        res = -1

        while low <= high:
            mid = (low + high) // 2
            if can(mid):
                res = mid
                high = mid - 1  # try smaller bound
            else:
                low = mid + 1   # need larger bound

        return res
```

**Step-by-step:**

1. **Build reversed graph** — For each original edge `u → v (w)`, store `v → u (w)` so BFS from node 0 simulates "can 0 be reached by everyone?"

2. **Binary search** on the answer in `[1, max_weight]`. At each midpoint `mid`, call `can(mid)`.

3. **`can(bound)` — BFS on reversed graph** using only edges with weight `≤ bound`. If all `n` nodes are reachable from node 0 (i.e., `count == n`), then every node can reach 0 in the original graph with this weight limit.

4. **Narrow the search** — if `can(mid)` is true, record `mid` as a candidate and try smaller (`high = mid - 1`); otherwise, try larger (`low = mid + 1`).

5. Return `res` (`-1` if no feasible bound was found).

---

## Complexity

| | |
|---|---|
| **Time** | $O(E \log W)$ — binary search over $W$ (max edge weight), each step does $O(E)$ BFS |
| **Space** | $O(N + E)$ — reversed adjacency list + visited array |
