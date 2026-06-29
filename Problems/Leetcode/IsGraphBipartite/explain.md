## Problem

https://leetcode.com/problems/is-graph-bipartite/description/

Given an undirected graph with `n` nodes (numbered `0` to `n-1`) represented as an adjacency list, determine whether the graph is **bipartite**.

A graph is bipartite if its nodes can be split into two independent sets `A` and `B` such that every edge connects a node in `A` to a node in `B` — no edge connects two nodes within the same set.

---

## Observations

1. **Bipartite = 2-colorable.** A graph is bipartite if and only if you can color every node with one of two colors such that no two adjacent nodes share the same color.

2. **Odd cycles break bipartiteness.** If the graph contains any cycle of odd length, it cannot be 2-colored, making it non-bipartite.

3. **Disconnected graphs.** The graph may have multiple connected components. Each component must independently be bipartite for the whole graph to be bipartite.

4. **BFS/DFS color propagation.** Starting from any unvisited node, assign it color `0`. Every neighbor gets color `1`, their neighbors get color `0`, and so on. If we ever find a neighbor that is already colored with the color we are about to assign, a conflict exists → not bipartite.

---

## Solution Explanation

```python
class Solution:
    def isBipartite(self, graph: List[List[int]]) -> bool:
        n = len(graph)
        colors = [-1] * n                      # -1 means unvisited

        def bfs(start: int) -> bool:
            q = deque([(start, 0)])
            colors[start] = 0                  # seed: color the start node 0
            while q:
                node, color = q.popleft()
                next_color = (color + 1) % 2   # alternate between 0 and 1

                for adj in graph[node]:
                    if colors[adj] == -1:              # unvisited: color and enqueue
                        colors[adj] = next_color
                        q.append((adj, next_color))
                    else:
                        if next_color != colors[adj]:  # conflict: same color on both ends of an edge
                            return False
            return True

        for i in range(n):
            if colors[i] == -1:        # start BFS from every unvisited node
                if not bfs(i):         # handles disconnected components
                    return False
        return True
```

### Step-by-step walkthrough

| Step | What happens |
|------|-------------|
| Initialize | `colors` array of size `n`, all `-1` (uncolored). |
| Outer loop | Iterate over every node `i`. If `colors[i] == -1`, the node belongs to an unexplored component — launch BFS from it. |
| BFS seed | Assign color `0` to `start`, push `(start, 0)` into the queue. |
| Expand | Pop `(node, color)`. Compute `next_color = 1 - color`. For each neighbor `adj`: |
| — Unvisited neighbor | Assign `next_color`, push to queue. |
| — Already colored neighbor | If its color equals `next_color`, two adjacent nodes share the same color → return `False`. |
| All components pass | Return `True`. |

### Complexity

| | |
|---|---|
| Time | $O(V + E)$ — every node and edge is visited once. |
| Space | $O(V)$ — the `colors` array and the BFS queue. |
