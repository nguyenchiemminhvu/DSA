## Problem Description

https://leetcode.com/problems/minimum-edge-reversals-so-every-node-is-reachable

```
There is a simple directed graph with n nodes labeled from 0 to n - 1. The graph
would form a tree if its edges were bi-directional.

You are given an integer n and a 2D integer array edges, where edges[i] = [ui, vi]
represents a directed edge going from node ui to node vi.

An edge reversal changes the direction of an edge, i.e., a directed edge going
from node ui to node vi becomes a directed edge going from node vi to node ui.

For every node i in the range [0, n - 1], your task is to independently calculate
the minimum number of edge reversals required so it is possible to reach any
other node starting from node i through a sequence of directed edges.

Return an integer array answer, where answer[i] is the minimum number of edge
reversals required so it is possible to reach any other node starting from
node i through a sequence of directed edges.

Example 1:

Input: n = 4, edges = [[2,0],[2,1],[1,3]]
Output: [1,1,0,2]

Example 2:

Input: n = 3, edges = [[1,2],[2,0]]
Output: [2,0,1]

Constraints:

2 <= n <= 10^5
edges.length == n - 1
0 <= ui == edges[i][0] < n
0 <= vi == edges[i][1] < n
ui != vi
The input is generated such that if the edges were bi-directional, the graph
would be a tree.
```

## Observations

### Underlying structure is a tree
- Ignoring direction, the graph has `n` nodes and `n - 1` edges and is connected, so it is a **tree**.
- Between any two nodes there is **exactly one** undirected path. To reach every node from a chosen root, every edge on that path must point *away* from the root. Any edge that points the wrong way must be reversed exactly once.

### Reversal cost as edge weights
- Build an undirected adjacency list, but tag each edge with a cost depending on the direction we traverse it:
    - For an original directed edge `u → v`:
        - traversing `u → v` costs `0` (already aligned with the outgoing direction needed from a root on the `u` side).
        - traversing `v → u` costs `1` (we'd need to reverse this edge to go that way).
- Then `answer[i]` is simply the **sum of edge costs over every tree edge**, where each edge's cost is determined by the direction we walk it away from root `i`.

### Brute force vs. re-rooting
- A naive solution runs DFS/BFS from every node: `O(n^2)` — too slow for `n = 10^5`.
- Key insight: when we move the root from a node `u` to its neighbor `v`, **only the single edge `(u, v)` changes its contribution**; every other edge is traversed in the same direction as before.
    - If the original edge is `u → v` (cost `0` from `u`, cost `1` from `v`), rooting at `v` flips that edge's contribution from `0` to `1`: `answer[v] = answer[u] + 1`.
    - If the original edge is `v → u` (cost `1` from `u`, cost `0` from `v`), the contribution flips from `1` to `0`: `answer[v] = answer[u] - 1`.
- This is the classic **re-rooting technique** on trees and runs in `O(n)`.

## Solution

### Approach: Re-rooting on a weighted undirected tree

Two DFS passes:
1. **Pass 1 (`dfs_init`)** — compute `answer[0]` by summing the reversal cost of every edge when the tree is rooted at node `0`.
2. **Pass 2 (`dfs_reroot`)** — propagate the answer from each node to its children using the `±1` update rule above.

#### Step-by-Step Explanation

1. **Build the weighted undirected adjacency list**:
    ```python
    adj = defaultdict(list)
    for u, v in edges:
        adj[u].append((v, 0))  # u -> v exists; going u to v costs 0
        adj[v].append((u, 1))  # going v to u requires a reversal; costs 1
    ```
    Each undirected edge appears twice — once with weight `0` in its natural direction, once with weight `1` in the opposite direction.

2. **Pass 1: compute the answer at the chosen root (node `0`)**:
    ```python
    def dfs_init(root, parent):
        rev_count = 0
        for next_node, weight in adj[root]:
            if next_node == parent:
                continue
            rev_count += weight + dfs_init(next_node, root)
        return rev_count

    res[0] = dfs_init(0, -1)
    ```
    Walk the tree from node `0`. For every edge we descend, add its weight (`0` if the directed edge already points away from `0`, `1` otherwise). The `parent` argument prevents walking back up the edge we just came from.

3. **Pass 2: re-root to compute every other answer in `O(n)`**:
    ```python
    def dfs_reroot(root, parent):
        for next_node, weight in adj[root]:
            if next_node == parent:
                continue

            if weight == 0:
                # Edge root -> next_node was "free" from root.
                # From next_node, traversing it the other way now costs 1.
                res[next_node] = res[root] + 1
            else:
                # Edge was already a reversal from root (cost 1).
                # From next_node, the edge is naturally outgoing — saves 1.
                res[next_node] = res[root] - 1

            dfs_reroot(next_node, root)

    dfs_reroot(0, -1)
    ```
    Only the single edge between `root` and `next_node` changes its contribution; all other edges remain traversed in the same direction. The answer therefore differs by exactly `+1` or `-1`.

4. **Return `res`** — the array of minimum reversal counts for every starting node.

### Why the `±1` update is correct

Fix any edge `e` other than `e' = (root, next_node)`. The unique tree path from `next_node` to any node `w` either:
- never uses `e`: contribution unchanged, or
- uses `e`: the path from `root` to `w` also used `e` in the **same** direction, because the only place the two paths can differ is on the single edge `e'`.

So `e'` is the only edge whose traversal direction changes between rooting at `root` and rooting at `next_node`. Its cost flips between `0` and `1`, giving the `+1 / -1` recurrence.

### Worked example (Example 1)

`edges = [[2,0],[2,1],[1,3]]`, tree shape: `0 — 2 — 1 — 3` with directions `2→0`, `2→1`, `1→3`.

Root at `0`:
- edge `0—2` walked as `0→2` costs `1` (original is `2→0`).
- edge `2—1` walked as `2→1` costs `0`.
- edge `1—3` walked as `1→3` costs `0`.
- `answer[0] = 1`.

Re-root `0 → 2` along original edge `2→0` (weight from `0`'s side is `1`): `answer[2] = answer[0] - 1 = 0`. ✓

Re-root `2 → 1` along original edge `2→1` (weight from `2`'s side is `0`): `answer[1] = answer[2] + 1 = 1`. ✓

Re-root `1 → 3` along original edge `1→3` (weight from `1`'s side is `0`): `answer[3] = answer[1] + 1 = 2`. ✓

Final: `[1, 1, 0, 2]`.

### Complexity

- **Time**: `O(n)` — each DFS visits every node and edge once; two passes total.
- **Space**: `O(n)` — adjacency list plus recursion stack. For `n = 10^5`, raise the recursion limit (`sys.setrecursionlimit`) or convert the DFS to an iterative stack-based version to avoid Python's default recursion cap.

