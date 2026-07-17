## Problem

https://leetcode.com/problems/flower-planting-with-no-adjacent/

You have `n` gardens labeled from `1` to `n`, and an array `paths` where `paths[i] = [xi, yi]` describes a bidirectional path between garden `xi` and garden `yi`. In each garden, you want to plant one of **4 types of flowers**.

All gardens have **at most 3 paths** coming into or leaving it.

Choose a flower type for each garden such that, for any two gardens connected by a path, they have **different types of flowers**.

Return any valid choice as an array `answer`, where `answer[i]` is the flower type planted in the `(i+1)`th garden. Flower types are denoted `1, 2, 3, 4`. It is guaranteed an answer always exists.

**Examples:**
```
Input: n = 3, paths = [[1,2],[2,3],[3,1]]
Output: [1,2,3]

Input: n = 4, paths = [[1,2],[3,4]]
Output: [1,2,1,2]

Input: n = 4, paths = [[1,2],[2,3],[3,4],[4,1],[1,3],[2,4]]
Output: [1,2,3,4]
```

---

## Observations

1. **Graph coloring problem:** This is essentially a graph coloring problem — assign a "color" (flower type 1–4) to each node (garden) such that no two adjacent nodes share the same color.

2. **At most 3 neighbors per node:** The key constraint is that every garden has at most 3 paths. Since there are 4 flower types and each node has at most 3 neighbors, there is **always at least one available color** for any node, regardless of what colors its neighbors already have. This guarantees a solution always exists with just 4 colors.

3. **Graph may be disconnected:** The gardens don't form a single connected component necessarily — some gardens may have no paths at all. We must handle all components.

4. **Greedy coloring is sufficient:** Because of constraint (2), a simple greedy approach — assign the smallest available color not used by any already-colored neighbor — always works. No backtracking is needed.

5. **BFS or DFS traversal:** We can traverse the graph (BFS or DFS) and greedily assign colors. The order of traversal doesn't matter because the guarantee of ≤ 3 neighbors ensures we never get stuck.

---

## Solution Explanation

The solution uses **BFS traversal with greedy coloring**:

1. **Build an adjacency list** from the `paths` input (0-indexed internally).

2. **Initialize a `colors` array** of size `n` with `-1` (uncolored), and a `visited` set to track processed nodes.

3. **Iterate over all nodes** `0` to `n-1`. For each unvisited node, start a BFS:
   - For each node dequeued (`cur`), collect all colors already assigned to its neighbors (`used_colors`).
   - Assign `cur` the **smallest color in `{1,2,3,4}`** not in `used_colors`.
   - Enqueue all unvisited neighbors.

4. Since each node has at most 3 neighbors, `used_colors` has at most 3 elements, so there is always a free color among `{1,2,3,4}`.

5. Return the `colors` array.

**Complexity:**
- Time: $O(n + E)$ where $E$ is the number of paths (each node and edge visited once).
- Space: $O(n + E)$ for the adjacency list, colors array, and BFS queue.

---

## Solution

```python
class Solution:
    def gardenNoAdj(self, n: int, paths: List[List[int]]) -> List[int]:
        graph = defaultdict(list)
        for u, v in paths:
            graph[u - 1].append(v - 1)
            graph[v - 1].append(u - 1)
        
        colors = [-1] * n
        visited = set()
        for i in range(n):
            if i not in visited:
                visited.add(i)
                q = deque([i])
                while q:
                    cur = q.popleft()
                    used_colors = set()
                    for adj in graph[cur]:
                        if colors[adj] != -1:
                            used_colors.add(colors[adj])
                    for color in range(1, 5):
                        if color not in used_colors:
                            colors[cur] = color
                            break
                    
                    for adj in graph[cur]:
                        if adj not in visited:
                            visited.add(adj)
                            q.append(adj)
        
        return colors
```
