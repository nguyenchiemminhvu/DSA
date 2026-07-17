## Problem

https://leetcode.com/problems/find-closest-node-to-given-two-nodes/description/

You are given a directed graph of `n` nodes numbered from `0` to `n - 1`, where **each node has at most one outgoing edge**.

The graph is represented with a 0-indexed array `edges` of size `n`, where `edges[i]` indicates a directed edge from node `i` to node `edges[i]`. If there is no outgoing edge from `i`, then `edges[i] == -1`.

Given two integers `node1` and `node2`, return the **index of the node** that can be reached from both `node1` and `node2`, such that the **maximum** of the two distances (from `node1` to that node, and from `node2` to that node) is **minimized**. If there are multiple answers, return the node with the **smallest index**. If no such node exists, return `-1`.

---

## Observations

1. **Functional graph structure**: Each node has at most one outgoing edge, so the graph is a *functional graph*. From any starting node, following the edges forms a simple path that eventually either terminates (hits a `-1`) or enters a cycle.

2. **BFS is sufficient for distances**: Since all edges have equal weight (cost = 1), a simple BFS (or even linear traversal following `edges[i]`) from each of `node1` and `node2` gives the shortest distances to all reachable nodes.

3. **Cycles must be handled**: Because the graph may contain cycles, we need visited tracking to avoid infinite loops during traversal.

4. **Minimizing the maximum**: For each candidate node `i`, the cost is `max(dist1[i], dist2[i])`. We want the node that minimizes this value. Iterating all nodes in order `0..n-1` and taking the first minimum naturally handles the "smallest index" tiebreaker.

5. **Reachability check**: A candidate node is only valid if both `dist1[i]` and `dist2[i]` are finite (i.e., the node is reachable from both `node1` and `node2`).

---

## Solution Explanation

```python
class Solution:
    def closestMeetingNode(self, edges: List[int], node1: int, node2: int) -> int:
        INF = float('inf')
        n = len(edges)

        # Build adjacency list (each node has at most one neighbor)
        graph = defaultdict(list)
        for i in range(len(edges)):
            if edges[i] != -1:
                graph[i].append(edges[i])
        
        # BFS to compute shortest distances from a given source node
        def shortest_path(node: int) -> List[int]:
            dist = [INF] * n
            dist[node] = 0
            q = deque([(0, node)])
            while q:
                d, node = q.popleft()
                if d > dist[node]:   # stale entry — skip
                    continue
                
                for adj in graph[node]:
                    if d + 1 < dist[adj]:
                        dist[adj] = d + 1
                        q.append((dist[adj], adj))
            return dist
        
        dist1 = shortest_path(node1)   # distances from node1 to all nodes
        dist2 = shortest_path(node2)   # distances from node2 to all nodes

        shortest = INF
        res_node = -1
        for i in range(n):             # iterate in order to prefer smallest index
            d1 = dist1[i]
            d2 = dist2[i]
            if d1 != INF and d2 != INF:            # node i is reachable from both
                if shortest > max(d1, d2):         # found a better meeting node
                    res_node = i
                    shortest = max(d1, d2)
        
        return res_node
```

### Step-by-step walkthrough

| Step | Action |
|------|--------|
| 1 | Build an adjacency list from the `edges` array. |
| 2 | Run BFS from `node1` → `dist1[i]` = shortest distance from `node1` to node `i`. |
| 3 | Run BFS from `node2` → `dist2[i]` = shortest distance from `node2` to node `i`. |
| 4 | Iterate over all nodes `0..n-1`. For each node reachable from **both** sources, compute `max(dist1[i], dist2[i])`. Track the global minimum and the corresponding node index. |
| 5 | Return the best node index, or `-1` if none exists. |

### Why BFS over simple traversal?

Although each node has at most one outgoing edge (making a simple pointer-following loop possible), using BFS with a `dist` array naturally handles **cycle detection** via the stale-entry check (`if d > dist[node]: continue`). Both approaches are O(n), but BFS generalizes cleanly.

### Complexity

- **Time**: O(n) — two BFS passes each visiting at most `n` nodes, plus one linear scan.
- **Space**: O(n) — distance arrays and BFS queue.

### Example trace (Example 1)

```
edges = [2, 2, 3, -1], node1 = 0, node2 = 1

dist1 (from 0): [0, INF, 1, 2]
dist2 (from 1): [INF, 0, 1, 2]

Candidates:
  node 2: max(1, 1) = 1  ✓ best so far
  node 3: max(2, 2) = 2  ✗ worse

Answer: 2
```
