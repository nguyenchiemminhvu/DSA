## Problem

https://leetcode.com/problems/shortest-distance-after-road-addition-queries-i/description/

You are given an integer `n` and a 2D integer array `queries`. There are `n` cities numbered from `0` to `n - 1`. Initially, there is a unidirectional road from city `i` to city `i + 1` for all `0 <= i < n - 1`.

`queries[i] = [ui, vi]` represents the addition of a new unidirectional road from city `ui` to city `vi`. After each query, find the length of the shortest path from city `0` to city `n - 1`.

Return an array `answer` where `answer[i]` is the length of the shortest path from city `0` to city `n - 1` after processing the first `i + 1` queries.

---

## Observations

- The initial graph is a simple chain: `0 → 1 → 2 → ... → n-1`, so the initial shortest path has length `n - 1`.
- Each query adds a "shortcut" edge `(u, v)` where `v - u > 1`, which can potentially reduce the shortest path.
- All edge weights are uniform (cost = 1 per edge), so **BFS** is the optimal shortest-path algorithm — no need for Dijkstra's weighted priority queue. However, using a deque with `(cost, node)` pairs still works correctly here.
- Since `n` and `queries.length` are both at most 500, running BFS after every query gives at most `500 × 500 = 250,000` operations — well within time limits.
- The graph is **directed** and only grows (edges are added, never removed), so we can incrementally add edges and re-run BFS each time.
- Because all edges have equal weight, BFS naturally visits nodes in order of increasing distance, guaranteeing the first time we reach `n - 1` is via the shortest path.

---

## Solution Explanation

```python
class Solution:
    def shortestDistanceAfterQueries(self, n: int, queries: List[List[int]]) -> List[int]:
        graph = defaultdict(list)
        for i in range(1, n):
            graph[i - 1].append(i)
        
        def shortest_path() -> int:
            INF = 0xFFFFFFFF
            dist = [INF] * n
            dist[0] = 0
            q = deque([(0, 0)])  # (cost, node)
            while q:
                cur_cost, cur_node = q.popleft()
                if cur_cost > dist[cur_node]:
                    continue
                
                for adj in graph[cur_node]:
                    if cur_cost + 1 < dist[adj]:
                        dist[adj] = cur_cost + 1
                        q.append((cur_cost + 1, adj))
            return dist[n - 1]
        
        res = []
        for u, v in queries:
            graph[u].append(v)
            res.append(shortest_path())
        return res
```

### Step-by-step breakdown

1. **Graph initialization**  
   Build an adjacency list representing the initial chain: `0 → 1 → 2 → ... → n-1`.

2. **BFS shortest path (`shortest_path`)**  
   - Initialize a `dist` array with infinity for all nodes.  
   - Start BFS from node `0` with cost `0`.  
   - For each node popped from the deque, attempt to relax all its neighbors. If a shorter path to a neighbor is found, update `dist` and push the neighbor onto the deque.  
   - The pruning condition `if cur_cost > dist[cur_node]: continue` avoids processing stale entries — this is what makes the deque approach (rather than pure BFS) safe here.  
   - Return `dist[n - 1]` as the shortest distance to the destination.

3. **Processing queries**  
   For each query `(u, v)`:
   - Add the directed edge `u → v` to the graph.
   - Run `shortest_path()` on the updated graph.
   - Append the result to the answer list.

### Complexity

| | Value |
|---|---|
| **Time** | $O(Q \times (V + E))$ where $Q$ = number of queries, $V = n$, $E$ grows up to $n + Q$ |
| **Space** | $O(V + E)$ for the adjacency list and distance array |

Given the constraints ($n, Q \leq 500$), this is efficient enough.
