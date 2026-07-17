## Problem

https://leetcode.com/problems/minimum-time-for-k-connected-components/description/

You are given an integer `n` and an undirected graph with `n` nodes labeled from `0` to `n - 1`. This is represented by a 2D array `edges`, where `edges[i] = [ui, vi, timei]` indicates an undirected edge between nodes `ui` and `vi` that can be removed at `timei`.

You are also given an integer `k`.

Initially, the graph may be connected or disconnected. Your task is to find the **minimum time** `t` such that after removing all edges with `time <= t`, the graph contains **at least k connected components**.

Return the minimum time `t`.

A **connected component** is a subgraph in which there exists a path between any two vertices, and no vertex shares an edge with a vertex outside of the subgraph.

### Examples

**Example 1:**
```
Input: n = 2, edges = [[0,1,3]], k = 2
Output: 3
```
Initially, there is one connected component {0, 1}.
At time = 3, edge [0, 1] is removed, resulting in k = 2 connected components {0}, {1}.

**Example 2:**
```
Input: n = 3, edges = [[0,1,2],[1,2,4]], k = 3
Output: 4
```
At time = 2, edge [0,1] is removed → 2 components. At time = 4, edge [1,2] is removed → 3 components.

**Example 3:**
```
Input: n = 3, edges = [[0,2,5]], k = 2
Output: 0
```
Already k = 2 disconnected components {1}, {0, 2} from the start.

### Constraints
- `1 <= n <= 10^5`
- `0 <= edges.length <= 10^5`
- `edges[i] = [ui, vi, timei]`
- `0 <= ui, vi < n`, `ui != vi`
- `1 <= timei <= 10^9`
- `1 <= k <= n`
- No duplicate edges

## Observations

1. **Monotonic property:** As time `t` increases, more edges are removed, so the number of connected components can only **increase or stay the same**. This is the key insight that enables binary search.

2. **Reformulation:** "After removing all edges with `time <= t`" is equivalent to keeping only edges with `time > t`. So we want the smallest `t` such that only retaining edges with `time > t` yields at least `k` connected components.

3. **Checking a given `t`:** Build a DSU (Disjoint Set Union) structure with only the edges where `time > t`. If the number of components is `>= k`, then `t` is valid.

4. **Binary search over `t`:** Since the number of components is monotonically non-decreasing with `t`, we can binary search on the answer in the range `[0, 10^9]`.

5. **Edge case:** If the graph already has `>= k` components with no edges removed (`t = 0`), return `0`.

## Solution

### Approach: Binary Search + Disjoint Set Union (DSU)

We binary search on the answer `t`. For each candidate `t`, we use DSU to count connected components when only edges with `time > t` are retained.

```python
class DSU:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [0] * size
        self.components = size

    def find(self, i):
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])
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
            self.components -= 1
            return True
        return False

class Solution:
    def minTime(self, n: int, edges: List[List[int]], k: int) -> int:
        low, high = 0, 10**9
        res = high + 1
        while low <= high:
            mid = low + (high - low) // 2

            dsu = DSU(n)
            for u, v, t in edges:
                if t > mid:
                    dsu.union(u, v)
            
            valid = dsu.components >= k
            if valid:
                res = mid
                high = mid - 1
            else:
                low = mid + 1
        return res
```

### How It Works

1. **DSU Initialization:** Every node starts as its own component, so `components = n`.

2. **Binary search** over time range `[0, 10^9]`:
   - For each `mid`, build a fresh DSU and union only edges with `time > mid` (these edges survive at time `mid`).
   - If `dsu.components >= k`, then `mid` is a valid answer — record it and try smaller times.
   - Otherwise, we need to remove more edges, so increase `mid`.

3. **Result:** The smallest valid `mid` found during binary search is returned.

### Example Walkthrough

For `n = 3, edges = [[0,1,2],[1,2,4]], k = 3`:

| `mid` | Edges kept (`time > mid`) | Components | Valid? |
|-------|--------------------------|------------|--------|
| 500000000 | none | 3 | ✅ → res=500000000, high=499999999 |
| ... | ... | ... | ... |
| 3 | [1,2,4] | 2 | ❌ → low=4 |
| 4 | none | 3 | ✅ → res=4, high=3 |
| low > high → stop | | | |

Answer: **4**

### Complexity Analysis

- **Time Complexity:** $O(E \cdot \log(\text{maxTime}) \cdot \alpha(n))$
  - Binary search: $O(\log(10^9)) \approx 30$ iterations
  - Each iteration processes all `E` edges through DSU with near-constant $\alpha(n)$ per operation
- **Space Complexity:** $O(n)$ — for the DSU parent and rank arrays

### Key Advantages

1. **Clean monotonicity:** The problem maps perfectly to binary search due to the monotonic relationship between time and component count.
2. **DSU efficiency:** Union-Find with path compression and union by rank handles connectivity queries in nearly O(1) amortized time.
3. **Simple validity check:** We only need to keep edges with `time > mid`, making the check straightforward.

# Tags

Binary Search, Union-Find (DSU), Graph, Connected Components

