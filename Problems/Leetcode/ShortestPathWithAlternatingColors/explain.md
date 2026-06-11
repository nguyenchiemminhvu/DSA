## Problem

https://leetcode.com/problems/shortest-path-with-alternating-colors/description/

Given a directed graph of `n` nodes (labeled `0` to `n-1`) with red and blue edges, find the shortest path from node `0` to every other node such that edge colors **alternate** along the path. Return an array `answer[x]` = shortest alternating path length from `0` to `x`, or `-1` if unreachable.

---

## Observations

1. **State = (node, last_edge_color)** — The same node can be reached in two fundamentally different states: arriving via a red edge or arriving via a blue edge. Each state must be tracked independently because they allow different next edges.

2. **BFS gives shortest path in unweighted graphs** — Each BFS level corresponds to one more edge traversed, so the first time we reach a node at a given state is guaranteed to be the shortest.

3. **Two starting conditions** — From node `0`, the first edge can be either red or blue. We run BFS twice: once assuming the first edge is red, once assuming blue. The final answer for each node is the minimum across both runs.

4. **Visited set must include color** — `visited` is keyed by `(is_red, node)` not just `node`. Without the color dimension, we might cut off valid alternating paths prematurely (e.g., reaching node `x` via red should not block reaching it via blue later, since blue arrival allows different next edges).

5. **Self-edges and parallel edges are handled naturally** — The adjacency list and visited-set approach handles them without special cases.

---

## Solution Explanation

```python
class Solution:
    def shortestAlternatingPaths(self, n: int, red_edges: List[List[int]], blue_edges: List[List[int]]) -> List[int]:
        res = [float('inf')] * n
        res[0] = 0

        mp_red = defaultdict(list)
        mp_blue = defaultdict(list)
        for u, v in red_edges:
            mp_red[u].append(v)
        for u, v in blue_edges:
            mp_blue[u].append(v)

        def bfs(start_with_red: bool):
            q = deque([(start_with_red, 0)])
            visited = set()
            visited.add((start_with_red, 0))
            steps = -1
            while q:
                steps += 1
                z = len(q)
                for _ in range(z):
                    is_red, node = q.popleft()
                    if steps < res[node]:
                        res[node] = steps

                    # If we arrived via red, next edge must be blue, and vice versa
                    adj = mp_blue[node] if is_red else mp_red[node]

                    for next_node in adj:
                        if (not is_red, next_node) not in visited:
                            visited.add((not is_red, next_node))
                            q.append((not is_red, next_node))

        bfs(True)   # first edge is red
        bfs(False)  # first edge is blue

        for i in range(1, n):
            if res[i] == float('inf'):
                res[i] = -1
        return res
```

### Step-by-step

1. **Build adjacency lists** separately for red and blue edges.

2. **`bfs(start_with_red)`** explores the graph starting from node `0`. The boolean `is_red` in each queue entry tracks the color of the **last edge used** to reach `node` (equivalently, the color of the **next required edge**).

3. **Level-by-level BFS** (`steps` increments once per level, `z = len(q)` captures the current frontier): when a node is dequeued at `steps` steps, we update `res[node]` if this is shorter than any previously found path.

4. **Alternation** is enforced by selecting the opposite adjacency list: arrived via red → follow blue edges; arrived via blue → follow red edges.

5. **Running BFS twice** covers both possible first-edge colors. `res` is shared and always stores the global minimum.

6. **Final pass** converts any remaining `inf` to `-1`.

### Complexity

- **Time:** $O(n + E)$ per BFS, where $E$ = total edges. Two BFS runs → $O(n + E)$ overall.
- **Space:** $O(n + E)$ for adjacency lists and the visited set.
