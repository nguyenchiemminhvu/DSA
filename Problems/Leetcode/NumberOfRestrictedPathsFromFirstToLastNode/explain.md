## Problem

https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/

Given an undirected weighted connected graph with `n` nodes (labeled `1` to `n`) and an array `edges` where `edges[i] = [ui, vi, weighti]` represents an edge between nodes `ui` and `vi`.

Define `distanceToLastNode(x)` as the **shortest distance** from node `x` to node `n` (Dijkstra from node `n`).

A **restricted path** from node `1` to node `n` is a path `[z0, z1, ..., zk]` such that:
- `z0 = 1`, `zk = n`
- For every consecutive pair: `distanceToLastNode(zi) > distanceToLastNode(zi+1)`

Return the **number of restricted paths** from node `1` to node `n`, modulo `10^9 + 7`.

**Example 1:**
```
Input: n = 5, edges = [[1,2,3],[1,3,3],[2,3,1],[1,4,2],[5,2,2],[3,5,1],[5,4,10]]
Output: 3
Restricted paths:
  1 --> 2 --> 5
  1 --> 2 --> 3 --> 5
  1 --> 3 --> 5
```

**Example 2:**
```
Input: n = 7, edges = [[1,3,1],[4,1,2],[7,3,4],[2,5,3],[5,6,1],[6,7,2],[7,5,3],[2,6,4]]
Output: 1
Restricted path: 1 --> 3 --> 7
```

**Constraints:**
- `1 <= n <= 2 * 10^4`
- `n - 1 <= edges.length <= 4 * 10^4`
- `1 <= ui, vi <= n`, `ui != vi`
- `1 <= weighti <= 10^5`
- At most one edge between any two nodes; at least one path between any two nodes.

---

## Observations

1. **`distanceToLastNode` is computed from node `n`**, not from node `1`. Run a **single Dijkstra from node `n`** on the undirected graph to get shortest distances `dist[v]` for all nodes `v`. Since the graph is undirected, this gives us `distanceToLastNode(v) = dist[v]`.

2. **The restricted path condition creates a DAG.** A move from node `u` to node `v` is valid on a restricted path only if `dist[u] > dist[v]`. This means all valid edges are directed from higher `dist` to lower `dist` — forming a **Directed Acyclic Graph (DAG)** with no cycles (since `dist` values are strictly decreasing along any path).

3. **Counting paths on a DAG naturally calls for Dynamic Programming.** Define `dp[v]` = number of restricted paths from node `v` to node `n`. The answer is `dp[1]`.
   - Base case: `dp[n] = 1`
   - Transition: for each neighbor `u` of `v`, if `dist[v] > dist[u]`, then `dp[v] += dp[u]`

4. **Topological ordering by `dist` value.** Since edges in the DAG go from larger `dist` to smaller `dist`, processing nodes in **increasing order of `dist`** gives a valid topological order. This avoids explicitly building the DAG — we can use memoization with DFS or process nodes sorted by `dist`.

5. **Modulo arithmetic** is required since the answer can be astronomically large. Apply `% (10^9 + 7)` during DP accumulation.

---

## Approach

### Step 1 — Dijkstra from node `n`
- Build an adjacency list for the undirected weighted graph.
- Run Dijkstra starting from node `n` to compute `dist[v]` = shortest distance from `v` to `n` for all nodes `v`.

### Step 2 — DP with memoization (top-down DFS)
- Define `dp[v]` = number of restricted paths from `v` to `n`.
- Start DFS from node `1`.
- For each node `v`, iterate over its neighbors `u`:
  - If `dist[v] > dist[u]`, recurse: `dp[v] += dp[u]`
- Memoize results to avoid recomputation.
- Return `dp[1] % (10^9 + 7)`.

### Alternatively — Bottom-up DP
- Sort all nodes in **increasing order of `dist`** (this gives topological order of the implicit DAG).
- Process nodes from smallest `dist` to largest:
  - For node `v`, for each neighbor `u` with `dist[u] < dist[v]`: `dp[v] += dp[u]`
- Return `dp[1]`.

### Complexity
- **Time:** `O((N + E) log N)` for Dijkstra + `O(N + E)` for DP = `O((N + E) log N)`
- **Space:** `O(N + E)` for adjacency list, distance array, and DP table
