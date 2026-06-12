## Problem

https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/description/

Given a weighted directed graph of `n` nodes (numbered `0` to `n-1`) and a list of directed edges `edges[i] = [from, to, weight]`, find the **minimum total weight** of a subgraph such that node `dest` is reachable from **both** `src1` and `src2`. Return `-1` if no such subgraph exists.

---

## Key Insight: The "Meeting Point" Trick

The two paths — one from `src1` to `dest` and one from `src2` to `dest` — must at some point **share edges** to minimize total weight (shared edges are only counted once in a subgraph). The optimal structure always looks like a **Y-shape**:

```
src1 ──────┐
           ├──→ common ──→ dest
src2 ──────┘
```

Both paths travel independently until they converge at some **common node**, after which they share a single path to `dest`. This is always at least as good as two fully separate paths, because any separate paths can be merged at the first node where they happen to intersect.

So the answer is:

$$\min_{\text{common} \in [0, n)} \Big( \text{dist}(src1 \to common) + \text{dist}(src2 \to common) + \text{dist}(common \to dest) \Big)$$

---

## Algorithm

We need three shortest-path arrays, each computed once using **Dijkstra's algorithm**:

| Array        | Meaning                                    | Graph used     |
|--------------|--------------------------------------------|----------------|
| `dist1[v]`   | Shortest distance from `src1` to node `v`  | Forward graph  |
| `dist2[v]`   | Shortest distance from `src2` to node `v`  | Forward graph  |
| `dist_dest[v]`| Shortest distance from node `v` to `dest` | Reverse graph  |

Computing `dist(v → dest)` efficiently is done by **reversing all edges** and running Dijkstra from `dest` on the reversed graph. A path `v → ... → dest` in the original graph becomes a path `dest → ... → v` in the reversed graph.

Then iterate over every candidate `common` node and return the minimum combined cost.

---

## Walkthrough — Example 1

```
n = 6
edges = [[0,2,2],[0,5,6],[1,0,3],[1,4,5],[2,1,1],[2,3,3],[2,3,4],[3,4,2],[4,5,1]]
src1 = 0, src2 = 1, dest = 5
```

After running Dijkstra three times:

| node | dist1 (from 0) | dist2 (from 1) | dist_dest (to 5) |
|------|---------------|---------------|-----------------|
| 0    | 0             | 3             | 6               |
| 1    | 3             | 0             | 6               |
| 2    | 2             | 3             | 6               |
| 3    | 5             | 6             | 3               |
| 4    | 7             | 5             | 1               |
| 5    | 6             | 7             | 0               |

Checking each `common` node:
- common = 0: 0 + 3 + 6 = **9** ✓
- common = 1: 3 + 0 + 6 = 9
- common = 4: 7 + 5 + 1 = 13
- common = 5: 6 + 7 + 0 = 13

Minimum = **9**

---

## Solution

```python
from collections import defaultdict
from typing import List
import heapq

class Solution:
    def minimumWeight(self, n: int, edges: List[List[int]], src1: int, src2: int, dest: int) -> int:
        INF = float('inf')
        adj = defaultdict(list)
        adj_rev = defaultdict(list)
        for u, v, d in edges:
            adj[u].append((d, v))
            adj_rev[v].append((d, u))     # reversed edge for dist(v -> dest)
        
        def shortest_path(source, rev: bool) -> List[int]:
            adj_ref = adj_rev if rev else adj
            
            dist = [INF] * n
            dist[source] = 0
            pq = [(0, source)]
            while pq:
                cur_dist, cur_node = heapq.heappop(pq)
                if cur_dist > dist[cur_node]:
                    continue
                for next_dist, next_node in adj_ref[cur_node]:
                    if dist[next_node] > cur_dist + next_dist:
                        dist[next_node] = cur_dist + next_dist
                        heapq.heappush(pq, (dist[next_node], next_node))
            return dist
        
        dist1     = shortest_path(src1, False)   # src1  -> every node
        dist2     = shortest_path(src2, False)   # src2  -> every node
        dist_dest = shortest_path(dest, True)    # every node -> dest

        res = INF
        for common in range(n):
            if dist1[common] != INF and dist2[common] != INF and dist_dest[common] != INF:
                res = min(res, dist1[common] + dist2[common] + dist_dest[common])
        
        return -1 if res == INF else res
```

---

## Complexity

| | Complexity |
|---|---|
| **Time** | $O((V + E) \log V)$ — three Dijkstra runs |
| **Space** | $O(V + E)$ — adjacency lists + distance arrays |

where $V = n$ and $E = |edges|$.
