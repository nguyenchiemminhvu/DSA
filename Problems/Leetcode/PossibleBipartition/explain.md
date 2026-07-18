## Problem

https://leetcode.com/problems/possible-bipartition/description/

Split `n` people (labeled `1` to `n`) into two groups such that no two people who dislike each other are in the same group. Return `true` if such a split is possible.

**Example 1:**
```
Input: n = 4, dislikes = [[1,2],[1,3],[2,4]]
Output: true
Explanation: Group 1 = [1,4], Group 2 = [2,3]
```

**Example 2:**
```
Input: n = 3, dislikes = [[1,2],[1,3],[2,3]]
Output: false
Explanation: Person 2 and 3 both dislike each other and both dislike person 1 — impossible to split into 2 groups.
```

---

## Key Insight

This is a **graph bipartiteness** problem. Model each person as a node and each dislike pair as an undirected edge. The question becomes: *can the graph be 2-colored such that no two adjacent nodes share the same color?*

A graph is **bipartite** if and only if it contains **no odd-length cycle**.

---

## Solution: BFS Graph Coloring

```python
class Solution:
    def possibleBipartition(self, n: int, dislikes: List[List[int]]) -> bool:
        graph = defaultdict(list)
        for u, v in dislikes:
            graph[u - 1].append(v - 1)
            graph[v - 1].append(u - 1)
        
        colors = [-1] * n
        for i in range(n):
            if colors[i] == -1: # not yet give color
                q = deque([(0, i)])
                while q:
                    color, node = q.popleft()
                    colors[node] = color
                    for adj in graph[node]:
                        if colors[adj] == -1:
                            q.append(((color + 1) % 2, adj))
                        else:
                            if colors[adj] == color:
                                return False
        return True
```

### Step-by-step Explanation

**1. Build an undirected adjacency list**

Convert each `[ai, bi]` dislike pair into a bidirectional edge (using 0-indexed nodes). Two people who dislike each other must end up in *different* groups, so they are connected by an edge.

**2. BFS coloring**

Use a `colors` array (initialized to `-1` = unvisited) to assign each node color `0` or `1`, representing the two groups.

The outer `for` loop ensures **disconnected components** are all visited — the graph may not be fully connected.

For each unvisited node, start a BFS:
- Assign the current node its color.
- For each neighbor:
  - If **unvisited** → assign the opposite color `(color + 1) % 2` and enqueue.
  - If **already colored** → check if it has the *same* color as the current node. If so, a conflict exists → return `False`.

**3. Return result**

If BFS completes without any conflict across all components, the graph is bipartite → return `True`.

---

## Complexity

| | |
|---|---|
| Time | $O(V + E)$ — each node and edge is visited once |
| Space | $O(V + E)$ — adjacency list + colors array + BFS queue |

where $V = n$ and $E = |\text{dislikes}|$.
