## Problem

https://leetcode.com/problems/critical-connections-in-a-network/description/

There are `n` servers numbered from `0` to `n - 1` connected by undirected server-to-server `connections`, where `connections[i] = [ai, bi]` represents a connection between servers `ai` and `bi`. Any server can reach any other server directly or indirectly.

A **critical connection** is a connection that, if removed, will make some servers unable to reach some other server.

Return all critical connections in any order.

**Example:**
```
Input:  n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
```
- Removing `[1,3]` isolates server `3`. All other edges belong to the cycle `0-1-2-0`, so removing any of them still leaves those servers connected.

---

## Observations

1. **Cycle edges are never critical.** If an edge `(u, v)` is part of a cycle, removing it still leaves an alternative path between `u` and `v` through the rest of the cycle. Therefore it cannot be a bridge.

2. **Tree edges outside any cycle are always critical.** If removing edge `(u, v)` splits the graph into two disconnected components, it is a bridge — i.e., a critical connection.

3. **The problem reduces to finding all bridges in an undirected graph.**

4. **DFS reveals cycle membership.** During a DFS traversal, a back-edge (an edge to an already-visited ancestor) signals the presence of a cycle. The key insight is to track the *lowest discovery time reachable* from each subtree.

---

## Approach — Tarjan's Bridge-Finding Algorithm

### Core Idea

Run a single DFS and maintain two arrays for every node `u`:

| Array | Meaning |
|-------|---------|
| `disc[u]` | Discovery time — when `u` was first visited (monotonically increasing) |
| `low[u]`  | Lowest discovery time reachable from the subtree rooted at `u` (via zero or more tree edges, then at most one back-edge) |

An edge `(u, v)` — where `v` is a child of `u` in the DFS tree — is a **bridge** if and only if:

$$\text{low}[v] > \text{disc}[u]$$

This condition means: `v` (and its entire subtree) has **no back-edge** reaching `u` or any ancestor of `u`. Therefore the only path from `v`'s subtree to `u`'s part of the graph is through edge `(u, v)` itself — making it critical.

### Update Rules for `low[u]`

While visiting node `u` with DFS:

- **Unvisited neighbor `v`** (tree edge): recurse into `v`, then pull up:
  ```
  low[u] = min(low[u], low[v])
  ```
- **Already-visited neighbor `v` that is NOT the parent** (back-edge): a cycle is detected, so:
  ```
  low[u] = min(low[u], disc[v])
  ```
  We use `disc[v]` (not `low[v]`) here because we can only "jump" to `v` directly, not further up via `v`'s own back-edges, in a single hop.

### Bridge Detection

After the recursive call `dfs(v)` returns back to `u`:
```
if low[v] > disc[u]:
    result.add([u, v])   // (u, v) is a critical connection
```

### Algorithm Walkthrough on Example 1

```
n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]

Adjacency list:
  0: [1, 2]
  1: [0, 2, 3]
  2: [1, 0]
  3: [1]

DFS from 0 (timer starts at 0):
  Visit 0: disc[0]=0, low[0]=0
    Visit 1: disc[1]=1, low[1]=1
      Visit 2: disc[2]=2, low[2]=2
        Neighbor 1 (parent): skip
        Neighbor 0 (visited, not parent): low[2] = min(2, disc[0]) = 0
      Back at 1: low[1] = min(1, low[2]) = 0
                 low[2]=0 > disc[1]=1? NO → (1,2) not a bridge
      Visit 3: disc[3]=3, low[3]=3
        Neighbor 1 (parent): skip
      Back at 1: low[1] = min(0, low[3]) = 0
                 low[3]=3 > disc[1]=1? YES → (1,3) is a bridge ✓
    Back at 0: low[0] = min(0, low[1]) = 0

Result: [[1,3]]
```

### Complexity

| | Complexity |
|---|---|
| Time  | $O(V + E)$ — single DFS pass |
| Space | $O(V + E)$ — adjacency list + recursion stack + `disc`/`low` arrays |
