## Problem

https://leetcode.com/problems/minimum-time-to-reach-destination-in-directed-graph/description/

You are given an integer `n` and a directed graph with `n` nodes labeled `0` to `n-1`. Each edge `[u, v, start, end]` can only be traversed at integer time `t` where `start <= t <= end`. Starting at node `0` at time `0`, you may wait at any node or travel along an available edge (costs 1 unit of time). Return the **minimum time** to reach node `n-1`, or `-1` if impossible.

---

## Observations

1. **Waiting is allowed.** You can stay at a node as long as needed, so if an edge opens in the future you can simply wait for it.

2. **An edge `[u, v, s, e]` is usable from node `u` at current time `t` when `t <= e`.**
   - If `t > e`: the edge has permanently closed — skip it.
   - If `t <= s`: depart at time `s`, arrive at `v` at time `s + 1`.
   - If `s < t <= e`: depart immediately, arrive at `v` at time `t + 1`.
   
   In all valid cases the arrival time is `max(t, s) + 1`.

3. **Minimising arrival time is equivalent to standard shortest-path with modified edge weights.** The "cost" of traversing edge `[u, v, s, e]` from time `t` is `max(t, s) + 1 - t` (which includes any waiting). Dijkstra naturally handles this because the priority queue always expands the node reachable at the earliest time.

4. **State is `(time, node)`.** Because waiting is free and we only care about the minimum arrival time at each node, `cost[node]` stores the best (minimum) time at which that node can be reached.

5. **Stale entries in the heap are discarded** with the standard `cur_time > cost[cur_node]` guard.

---

## Solution Explanation

```python
class Solution:
    def minTime(self, n: int, edges: List[List[int]]) -> int:
        graph = defaultdict(list)
        for u, v, s, e in edges:
            graph[u].append((v, s, e))
        
        INF = float('inf')
        cost = [INF] * n
        cost[0] = 0

        pq = [(0, 0)]  # (cur_time, cur_node)
        while pq:
            cur_time, cur_node = heapq.heappop(pq)
            if cur_time > cost[cur_node]:
                continue
            
            for adj, s, e in graph[cur_node]:
                if cur_time > e:       # edge already closed — unusable
                    continue
                
                # arrival time = max(cur_time, s) + 1
                next_time = s + 1          # cur_time <= s  →  wait, then travel
                if cur_time > s:
                    next_time = cur_time + 1  # s < cur_time <= e  →  travel now
                
                if next_time < cost[adj]:
                    cost[adj] = next_time
                    heapq.heappush(pq, (next_time, adj))
        
        return -1 if cost[n - 1] == INF else cost[n - 1]
```

**Step-by-step walkthrough:**

| Step | Action |
|------|--------|
| Build adjacency list | Each node maps to a list of `(neighbour, start, end)` tuples. |
| Initialise Dijkstra | `cost[0] = 0`; all others `INF`. Min-heap seeded with `(0, 0)`. |
| Pop `(cur_time, cur_node)` | Skip if stale (`cur_time > cost[cur_node]`). |
| For each outgoing edge | If `cur_time > e`: skip (edge expired). Otherwise compute `next_time = max(cur_time, s) + 1`. |
| Relax | If `next_time` improves `cost[adj]`, update and push to heap. |
| Answer | `cost[n-1]` if reachable, else `-1`. |

**Complexity:**
- Time: $O((V + E) \log V)$ — standard Dijkstra.
- Space: $O(V + E)$ for the graph and heap.
