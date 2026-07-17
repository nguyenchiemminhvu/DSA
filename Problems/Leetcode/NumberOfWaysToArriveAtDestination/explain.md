## Problem

https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/

Given a city of `n` intersections (numbered `0` to `n-1`) with bi-directional weighted roads, find the **number of ways** to travel from intersection `0` to intersection `n-1` in the **shortest possible time**. Return the answer modulo $10^9 + 7$.

---

## Observations

- This is a **shortest path counting** problem on a weighted undirected graph.
- A brute-force DFS approach (commented out in the solution) would enumerate all paths and track the minimum cost, but it's exponential in the worst case — too slow for `n` up to 200.
- **Dijkstra's algorithm** is the natural fit here since all edge weights are positive.
- The key insight: alongside the standard `dist[]` array tracking shortest distances, maintain a `ways[]` array tracking **how many shortest paths** reach each node.
  - When a shorter path to a neighbor is found → **reset** its way count to the current node's count.
  - When an equal-cost path to a neighbor is found → **add** the current node's count to it.
- A node's `ways` value is finalized once it is popped from the priority queue with its shortest distance (any later pop with a higher cost is skipped).

---

## Solution Explanation

```python
class Solution:
    def countPaths(self, n: int, roads: List[List[int]]) -> int:
        graph = defaultdict(list)
        for u, v, w in roads:
            graph[u].append((w, v))
            graph[v].append((w, u))

        mod = 10**9 + 7
        INF = float('inf')
        dist = [INF] * n
        dist[0] = 0
        ways = [0] * n
        ways[0] = 1

        pq = [(0, 0)]  # (cost, node)
        while pq:
            cur_cost, cur_node = heapq.heappop(pq)
            if cur_cost > dist[cur_node]:
                continue  # stale entry, skip

            for cost, adj_node in graph[cur_node]:
                next_cost = cur_cost + cost
                if next_cost < dist[adj_node]:
                    # Found a strictly shorter path → update distance and reset ways
                    dist[adj_node] = next_cost
                    ways[adj_node] = ways[cur_node] % mod
                    heapq.heappush(pq, (next_cost, adj_node))
                elif next_cost == dist[adj_node]:
                    # Found an equally short path → accumulate ways
                    ways[adj_node] = (ways[adj_node] + ways[cur_node]) % mod

        return ways[n - 1] % mod
```

### Step-by-step walkthrough (Example 1)

```
n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
```

| Step | Pop        | dist updated          | ways updated          |
|------|------------|-----------------------|-----------------------|
| 1    | (0, 0)     | dist[1]=2, dist[4]=5, dist[6]=7 | ways[1]=1, ways[4]=1, ways[6]=1 |
| 2    | (2, 1)     | dist[2]=5, dist[3]=5  | ways[2]=1, ways[3]=1  |
| 3    | (5, 2)     | dist[5]=6             | ways[5]=1             |
| 4    | (5, 3)     | dist[5]=6 (equal)     | ways[5]=2             |
| 5    | (5, 4)     | dist[6]=7 (equal)     | ways[6]=2             |
| 6    | (6, 5)     | dist[6]=7 (equal)     | ways[6]=4             |
| 7    | (7, 6)     | destination reached   | —                     |

Result: `ways[6] = 4` ✓

### Complexity

| | |
|---|---|
| **Time** | $O((V + E) \log V)$ — standard Dijkstra with a min-heap |
| **Space** | $O(V + E)$ — adjacency list, `dist[]`, `ways[]`, heap |
