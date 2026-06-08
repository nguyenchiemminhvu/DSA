## Problem

https://leetcode.com/problems/min-cost-to-connect-all-points/description/

You are given an array `points` representing integer coordinates of some points on a 2D-plane, where `points[i] = [xi, yi]`.

The cost of connecting two points `[xi, yi]` and `[xj, yj]` is the **Manhattan distance** between them: `|xi - xj| + |yi - yj|`.

Return the **minimum cost** to make all points connected. All points are connected if there is exactly one simple path between any two points.

**Example 1:**
```
Input:  points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
Output: 20
```

**Example 2:**
```
Input:  points = [[3,12],[-2,5],[-4,1]]
Output: 18
```

**Constraints:**
- `1 <= points.length <= 1000`
- `-10^6 <= xi, yi <= 10^6`
- All pairs `(xi, yi)` are distinct.

---

## Observations

1. **"Exactly one simple path between any two points"** is the definition of a **tree**. We need to connect all `n` points with exactly `n - 1` edges and no cycles — this is precisely a **Minimum Spanning Tree (MST)** problem.

2. **Every pair of points is a candidate edge.** With `n` points there are `n*(n-1)/2` possible edges, each with cost equal to the Manhattan distance between the two endpoints.

3. **Two classical MST algorithms apply here:**
   - **Prim's algorithm** — grows the MST one vertex at a time by always picking the cheapest edge connecting a visited vertex to an unvisited one.
   - **Kruskal's algorithm** — sorts all edges globally and greedily adds the cheapest edge that does not form a cycle, tracked efficiently with a **Disjoint Set Union (DSU)**.

4. **Prim's naive version** iterates over all unvisited nodes and all visited nodes at each step, giving $O(n^3)$ time — acceptable only for very small `n`.

5. **Kruskal's with a min-heap** builds all `O(n^2)` edges upfront, heapifies them, and pops edges until `n - 1` edges are accepted. DSU `find`/`union` runs in nearly $O(1)$ amortized, making the bottleneck the heap operations at $O(n^2 \log n)$.

6. **DSU with path compression and union by rank** ensures that cycle detection is essentially free, which is why Kruskal's is both simple to implement and fast in practice.

---

## Solution

### Approach 1: Prim's Algorithm (Greedy, Naive)

Start with node `0` in the visited set. At each step, scan every edge from any visited node to any unvisited node and pick the one with the minimum cost. Add that unvisited node to the visited set and accumulate the cost. Repeat until all `n` nodes are visited.

```python
def minCostConnectPoints(self, points: List[List[int]]) -> int:
    n = len(points)
    res = 0
    visited = set([0])
    while len(visited) < n:
        unvisited = set(range(n)) - visited
        min_dist = float('inf')
        chosen = -1
        for u in unvisited:
            for v in visited:
                dist = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1])
                if dist < min_dist:
                    min_dist = dist
                    chosen = u
        visited.add(chosen)
        res += min_dist
    return res
```

**Complexity Analysis:**
- **Time:** $O(n^3)$ — `n` outer iterations, each scanning up to $O(n^2)$ edges.
- **Space:** $O(n)$ — for the `visited` set.

**Step-by-step Walkthrough** — `points = [[0,0],[2,2],[3,10],[5,2],[7,0]]`

Label the points: A=0, B=1, C=2, D=3, E=4.

| Step | visited | Edges checked (unvisited → visited) | min\_dist | chosen |
|------|---------|-------------------------------------|-----------|--------|
| 1 | {A} | B→A:4, C→A:13, D→A:7, E→A:7 | **4** | **B** |
| 2 | {A,B} | C→{A,B}: min(13,9)=9, D→{A,B}: min(7,3)=3, E→{A,B}: min(7,7)=7 | **3** | **D** |
| 3 | {A,B,D} | C→{..}: min(13,9,10)=9, E→{..}: min(7,7,4)=4 | **4** | **E** |
| 4 | {A,B,D,E} | C→{..}: min(13,9,10,14)=**9** | **9** | **C** |

Total cost = 4 + 3 + 4 + 9 = **20** ✓

---

### Approach 2: Kruskal's Algorithm with DSU + Min-Heap

Build all `n*(n-1)/2` edges as `(distance, i, j)` tuples and push them into a min-heap. Pop edges in order of increasing cost. For each edge `(i, j)`, try to `union` the two endpoints in the DSU. If they were in different components (union succeeds), this edge is part of the MST — accumulate its cost and increment the edge counter. Stop as soon as `n - 1` edges are accepted.

```python
import heapq

class Solution:
    def minCostConnectPoints(self, points: List[List[int]]) -> int:
        n = len(points)

        class DSU:
            def __init__(self, size: int):
                self.parent = list(range(size))
                self.rank = [0] * size

            def find(self, i: int) -> int:
                if self.parent[i] == i:
                    return i
                self.parent[i] = self.find(self.parent[i])  # path compression
                return self.parent[i]

            def union(self, i: int, j: int) -> bool:
                root_i = self.find(i)
                root_j = self.find(j)
                if root_i == root_j:
                    return False                              # already connected → cycle
                if self.rank[root_i] < self.rank[root_j]:
                    self.parent[root_i] = root_j
                elif self.rank[root_i] > self.rank[root_j]:
                    self.parent[root_j] = root_i
                else:
                    self.parent[root_j] = root_i
                    self.rank[root_i] += 1
                return True

        dsu = DSU(n)
        edges = []
        for i in range(n):
            for j in range(i + 1, n):
                dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1])
                heapq.heappush(edges, (dist, i, j))

        count = 0
        total_cost = 0
        while edges:
            d, i, j = heapq.heappop(edges)
            if dsu.union(i, j):
                count += 1
                total_cost += d
                if count == n - 1:
                    break
        return total_cost
```

**Complexity Analysis:**
- **Time:** $O(n^2 \log n)$ — $O(n^2)$ edges are built and heapified; each of the $O(n^2)$ heap pops costs $O(\log n^2) = O(\log n)$; DSU operations are nearly $O(1)$ amortized.
- **Space:** $O(n^2)$ — for storing all edges in the heap.

**Step-by-step Walkthrough** — `points = [[0,0],[2,2],[3,10],[5,2],[7,0]]`

All edges sorted by distance (top of min-heap first):

| dist | i | j | Description |
|------|---|---|-------------|
| 3 | 1 | 3 | B–D |
| 4 | 0 | 1 | A–B |
| 4 | 3 | 4 | D–E |
| 7 | 0 | 3 | A–D |
| 7 | 0 | 4 | A–E |
| 7 | 1 | 4 | B–E |
| 9 | 1 | 2 | B–C |
| 10 | 2 | 3 | C–D |
| 13 | 0 | 2 | A–C |
| 14 | 2 | 4 | C–E |

Kruskal's steps:

| Pop | Edge | DSU before union | Union? | count | total\_cost |
|-----|------|-----------------|--------|-------|-------------|
| (3,1,3) | B–D | {0},{1},{2},{3},{4} | ✅ | 1 | 3 |
| (4,0,1) | A–B | {0},{1,3},{2},{4} | ✅ | 2 | 7 |
| (4,3,4) | D–E | {0,1,3},{2},{4} | ✅ | 3 | 11 |
| (7,0,3) | A–D | {0,1,3,4},{2} | ❌ same component | 3 | 11 |
| (7,0,4) | A–E | {0,1,3,4},{2} | ❌ same component | 3 | 11 |
| (7,1,4) | B–E | {0,1,3,4},{2} | ❌ same component | 3 | 11 |
| (9,1,2) | B–C | {0,1,3,4},{2} | ✅ | **4** | **20** |

`count == n - 1 = 4` → **stop**. Return **20** ✓

---

# Tags

`#graph` `#minimum-spanning-tree` `#kruskal` `#prim` `#disjoint-set-union` `#greedy` `#heap` `#union-find`
