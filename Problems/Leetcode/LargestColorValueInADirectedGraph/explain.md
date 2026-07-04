## Problem

https://leetcode.com/problems/largest-color-value-in-a-directed-graph/description/

Given a directed graph of `n` nodes and `m` edges, where each node `i` has a color `colors[i]` (a lowercase letter), find the **largest color value** of any valid path. The color value of a path is the count of the **most frequently occurring color** along that path. Return `-1` if the graph contains a cycle.

---

## Observations

1. **Cycle detection is mandatory.** If there is a cycle, no topological ordering exists and any path through the cycle is infinite — return `-1`.

2. **Topological order is the natural processing order.** To compute the best color count reachable at each node, we need all predecessors processed before a node. This is exactly what Kahn's algorithm (BFS-based topological sort) provides.

3. **State per node.** For each node `u` we want to know: *for every color `c`, what is the maximum count of `c` on any path ending at `u`?* This is a 2D DP table `dp[u][c]` of size `n × 26`.

4. **Transition.** When we relax an edge `u → v`:
   ```
   dp[v][c] = max(dp[v][c], dp[u][c])   for all c
   dp[v][colors[v]] += 1                 (node v itself contributes its own color)
   ```
   More precisely, after inheriting the best counts from `u`, we must add 1 for `v`'s own color **before** propagating further. So the correct order is:
   - Initialise `dp[v][colors[v]] = 1` when `v` is first enqueued (a path of length 1 at `v`).
   - When processing edge `u → v`: `dp[v][c] = max(dp[v][c], dp[u][c] + (c == colors[v] ? 1 : 0))`.

   A cleaner way: after the full topological traversal, `dp[v][c]` = max count of color `c` on any path **ending at** `v` (inclusive).

5. **Answer.** The global answer is `max over all nodes u, all colors c of dp[u][c]`.

6. **Cycle check with Kahn's.** If the number of nodes processed in the BFS is less than `n`, there is a cycle.

---

## Approach — Kahn's BFS + DP

### Data structures

| Structure | Purpose |
|---|---|
| `indegree[u]` | In-degree for Kahn's algorithm |
| `adj[u]` | Adjacency list |
| `dp[u][26]` | Best color-count on any path ending at `u` |
| `queue` | BFS queue seeded with nodes of indegree 0 |

### Algorithm

```
1. Build adjacency list and compute in-degrees.
2. Initialise dp[u][colors[u]] = 1 for all u.
3. Push all nodes with indegree 0 into the queue.
4. processed = 0, ans = 0
5. While queue is not empty:
     u = dequeue
     processed++
     ans = max(ans, max(dp[u][0..25]))
     For each neighbour v of u:
         For each color c in 0..25:
             dp[v][c] = max(dp[v][c], dp[u][c] + (c == colors[v] ? 1 : 0))
         indegree[v]--
         If indegree[v] == 0: enqueue v
6. If processed < n: return -1   // cycle detected
7. Return ans
```

### Complexity

- **Time:** $O(n \cdot 26 + m \cdot 26) = O((n + m) \cdot 26)$ — effectively $O(n + m)$.
- **Space:** $O(n \cdot 26)$ for the DP table.
