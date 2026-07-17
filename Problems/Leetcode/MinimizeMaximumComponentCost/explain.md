## Problem

https://leetcode.com/problems/minimize-maximum-component-cost/description/

You are given an undirected connected graph with `n` nodes (labeled `0` to `n-1`) and a 2D array `edges` where `edges[i] = [u, v, w]` is an undirected edge between `u` and `v` with weight `w`, and an integer `k`.

You may remove any number of edges so that the resulting graph has **at most** `k` connected components. The **cost** of a component is the **maximum edge weight** in that component (0 if no edges). Return the **minimum possible value of the maximum cost** across all components after such removals.

---

## Observations

1. **Removing edges = splitting components.** The graph starts fully connected (1 component). Every edge removal can potentially split it into more components. We want at most `k` components, so we can make at most `k - 1` cuts.

2. **Cost is determined by the heaviest retained edge.** Since cost of a component = its max edge weight, the overall maximum cost equals the weight of the single heaviest edge left in the entire graph. We want to minimize that.

3. **Reformulation:** Find the minimum weight threshold `W` such that, by keeping only edges with weight ≤ `W`, the graph has at most `k` connected components (i.e., the remaining edges are enough to hold it in ≤ k pieces).

4. **Greedy + DSU:** Instead of binary searching on `W`, we can simulate building the graph from scratch — adding edges in ascending weight order. We start with `n` isolated nodes (n components) and merge them. The moment the component count drops to `k`, the current edge weight is our answer. This works because:
   - Adding edges in sorted order is equivalent to scanning threshold `W` from 0 upward.
   - The first `W` at which the component count reaches `k` is the minimum possible answer.
   - Every component's maximum edge weight is ≤ `W` at that moment (we've only added edges with weight ≤ `W`).

5. **Edge case — `k == n`:** No edges are needed (every node is its own component), so the answer is 0. The DSU starts at `n` components and only decreases; since we never return inside the loop, the final `return 0` handles this correctly.

---

## Solution

```python
class DSU:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [0] * size
        self.components = size          # start: every node is its own component

    def find(self, i):                  # path compression
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])
        return self.parent[i]

    def union(self, i, j):              # union by rank
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i != root_j:
            if self.rank[root_i] < self.rank[root_j]:
                self.parent[root_i] = root_j
            elif self.rank[root_i] > self.rank[root_j]:
                self.parent[root_j] = root_i
            else:
                self.parent[root_j] = root_i
                self.rank[root_i] += 1
            self.components -= 1        # one fewer component after a real merge

class Solution:
    def minCost(self, n: int, edges: List[List[int]], k: int) -> int:
        edges.sort(key=lambda x: x[2])  # process cheapest edges first

        dsu = DSU(n)
        for u, v, w in edges:
            dsu.union(u, v)
            if dsu.components == k:     # reached target: current weight is the answer
                return w

        return 0                        # k >= n: no edges needed, cost is 0
```

### Step-by-step trace (Example 1)

`n=5, edges=[[0,1,4],[1,2,3],[1,3,2],[3,4,6]], k=2`

| Step | Edge added | Weight | Components |
|------|-----------|--------|------------|
| —    | —         | —      | 5          |
| 1    | (1,3)     | 2      | 4          |
| 2    | (1,2)     | 3      | 3          |
| 3    | (0,1)     | 4      | **2** → return **4** |

The edge (3,4,6) is effectively "removed" by never being added — it would split off as a separate component if we needed ≤ 2 components.

### Complexity

| | |
|---|---|
| **Time** | $O(E \log E)$ — dominated by sorting; DSU operations are near $O(1)$ amortized |
| **Space** | $O(n)$ for the DSU |
