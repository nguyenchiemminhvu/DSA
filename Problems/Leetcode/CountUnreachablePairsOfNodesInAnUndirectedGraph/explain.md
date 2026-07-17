## Problem

https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/

Given an integer `n` and a list of undirected edges, return the number of pairs of different nodes `(i, j)` such that there is **no path** connecting node `i` and node `j`.

---

## Observations

- The graph may be **disconnected**, meaning it can consist of several independent connected components.
- Two nodes are **unreachable from each other** if and only if they belong to **different connected components**.
- If two components have sizes `a` and `b`, they contribute `a * b` unreachable pairs.
- The total number of unreachable pairs is the sum of `size[i] * size[j]` for every pair of distinct components `(i, j)`.
- This can be computed efficiently using the **running prefix sum trick**:
  - As we iterate through components, for each component of size `v`, it forms `already_counted_nodes * v` new unreachable pairs with all previously seen nodes.

---

## Solution Explanation

### Step 1 — Build a Disjoint Set Union (DSU)

The `DSU` (Union-Find) data structure groups nodes into connected components.

- `find(i)` returns the **root representative** of node `i`'s component, using **path compression** for efficiency.
- `union(i, j)` merges the two components containing `i` and `j`, using **union by rank** to keep the tree shallow.

After processing all edges, every node that can reach each other shares the same root.

### Step 2 — Count component sizes

Iterate over all nodes `0..n-1`, call `find(i)` to get the root, and accumulate a frequency map `groups[root] → size`.

### Step 3 — Count unreachable pairs

Use the prefix sum trick over component sizes:

```
count_node = 0
res = 0
for each component of size v:
    res += count_node * v   # pairs between this component and all previous nodes
    count_node += v
```

This works because every node in the current component cannot reach any of the `count_node` nodes seen so far (they are in different components). Multiplying gives the exact number of new unreachable pairs introduced by this component.

### Complexity

| | |
|---|---|
| **Time** | $O(n \cdot \alpha(n))$ — nearly linear due to path compression + union by rank |
| **Space** | $O(n)$ — for parent/rank arrays and the groups map |

---

## Code

```python
class DSU:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [0] * size

    def find(self, i):
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])  # path compression
        return self.parent[i]

    def union(self, i, j):
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
            return True
        return False

class Solution:
    def countPairs(self, n: int, edges: List[List[int]]) -> int:
        dsu = DSU(n)
        for u, v in edges:
            dsu.union(u, v)
        
        # Map each root → size of its component
        groups = defaultdict(int)
        for i in range(n):
            root = dsu.find(i)
            groups[root] += 1
        
        # Prefix sum: count unreachable pairs across all component pairs
        count_node = 0
        res = 0
        for k, v in groups.items():
            res += (count_node * v)
            count_node += v
        return res
```

### Walkthrough — Example 2

`n = 7`, `edges = [[0,2],[0,5],[2,4],[1,6],[5,4]]`

After unions, components are:
- `{0, 2, 4, 5}` → size 4
- `{1, 6}` → size 2
- `{3}` → size 1

Prefix sum iteration:
| Step | Component size `v` | `res += count_node * v` | `count_node` |
|------|--------------------|-------------------------|--------------|
| 1    | 4                  | `0 * 4 = 0`             | 4            |
| 2    | 2                  | `4 * 2 = 8`             | 6            |
| 3    | 1                  | `6 * 1 = 6`             | 7            |

Total: `0 + 8 + 6 = 14` ✓
