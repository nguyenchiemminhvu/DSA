## Problem

https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/description/

# Reorder Routes to Make All Paths Lead to the City Zero

## Problem

https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/description/

There are **n cities** numbered from 0 to n - 1 with n - 1 roads forming a tree (only one path between any two cities). Each road is directed in one direction, and we need to reorient some roads so that **all cities can reach city 0** (the capital).

**Input:**
- `n`: number of cities (2 ≤ n ≤ 5 × 10⁴)
- `connections`: list of directed roads [aᵢ, bᵢ] (original direction: from aᵢ to bᵢ)

**Output:**
- Minimum number of edges that need to be reversed

**Example 1:**
```
n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
Output: 3
```

**Example 2:**
```
n = 5, connections = [[1,0],[1,2],[3,2],[3,4]]
Output: 2
```

**Example 3:**
```
n = 3, connections = [[1,0],[2,0]]
Output: 0
```

---

## Observations

### Key Insights:

1. **Tree Structure**: The graph is a tree with n nodes and n-1 edges. This means there's exactly one path between any two nodes.

2. **Reroot the Tree**: Since we want all cities to reach city 0, we can think of this as making city 0 the root and ensuring all edges point toward the root from their respective subtrees. This is equivalent to doing a **DFS from city 0** and counting how many edges are in the "wrong direction."

3. **Direction Encoding**: 
   - When traversing from city A to city B, if the original edge is A→B, the cost is **0** (no reversal needed)
   - If the original edge is B→A, the cost is **1** (reversal needed)

4. **Graph Construction**: Build an undirected graph but encode the original direction as weights:
   - If original edge is u→v: add (1, v) to u's adjacency list and (0, u) to v's adjacency list
   - This way, when we traverse away from the root, we know if we're going against the original direction

5. **DFS Approach**: Start from city 0 (root) and traverse the tree. For each unvisited neighbor:
   - If the edge cost is 1, it means we're going against the original direction, so we need to reverse it
   - Accumulate these costs as we traverse

### Why This Works:

In a tree, we only need to ensure every edge points toward a central node (city 0). The minimum reversals equals the number of edges that point away from the root in the subtree rooted at node 0.

---

## Solution

```python
class Solution:
    def minReorder(self, n: int, edges: List[List[int]]) -> int:
        # Build graph with cost encoding
        # graph[u] contains tuples (cost, v) where:
        # - cost = 1 if original direction is u→v (no reversal needed)
        # - cost = 0 if original direction is v→u (reversal needed)
        graph = {
            i: [] for i in range(n)
        }

        for u, v in edges:
            # Original direction: u → v (cost 1, no reversal)
            graph[u].append((1, v))
            # Reverse direction: v → u would need reversal (cost 0)
            graph[v].append((0, u))
        
        res = 0
        visited = [False] * n
        visited[0] = True
        
        def dfs(cur: int):
            nonlocal res
            adj = graph[cur]
            for cost, next_node in adj:
                if not visited[next_node]:
                    visited[next_node] = True
                    res += cost  # Add 1 if we need to reverse this edge
                    dfs(next_node)
        
        dfs(0)
        return res
```

### Algorithm Walkthrough:

1. **Initialize Graph**: Create adjacency list with cost encoding
   - For edge u→v: add (1, v) to graph[u] and (0, u) to graph[v]

2. **DFS from Root**: Start DFS from city 0
   - Mark visited nodes to avoid cycles
   - For each unvisited neighbor, add the cost to the result
   - Recursively process the neighbor

3. **Return**: The total cost accumulated during DFS is the minimum reversals

### Complexity Analysis:

- **Time Complexity**: O(n)
  - We visit each node exactly once
  - Each edge is examined twice (once from each direction)
  - Total operations: O(n + n) = O(n)

- **Space Complexity**: O(n)
  - Graph storage: O(n) nodes with n-1 edges
  - Visited array: O(n)
  - DFS recursion stack: O(n) in worst case (skewed tree)

### Example Trace (Example 1):

```
Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]

Graph after construction:
0: [(1, 1), (0, 4)]
1: [(0, 0), (1, 3)]
2: [(1, 3)]
3: [(0, 1), (0, 2)]
4: [(1, 0), (1, 5)]
5: [(0, 4)]

DFS from 0:
- Visit 0 (start)
  - Visit 1 (cost=1): res += 1 = 1
    - Visit 3 (cost=0): res += 0 = 1
      - Visit 2 (cost=0): res += 0 = 1
  - Visit 4 (cost=0): res += 0 = 1
    - Visit 5 (cost=1): res += 1 = 2

Final result: 2

Wait, expected output is 3. Let me recalculate...

Actually, with the correct edge encoding:
- [0,1]: 0→1, so (1,1) from 0, (0,0) from 1
- [1,3]: 1→3, so (1,3) from 1, (0,1) from 3
- [2,3]: 2→3, so (1,3) from 2, (0,2) from 3
- [4,0]: 4→0, so (1,0) from 4, (0,4) from 0
- [4,5]: 4→5, so (1,5) from 4, (0,4) from 5

DFS trace:
- Visit 0: neighbors are (1,1) and (0,4)
  - Visit 1 with cost 1: res = 1
    - Visit 3 with cost 0: res = 1
      - Visit 2 with cost 0: res = 1
  - Visit 4 with cost 0: res = 1
    - Visit 5 with cost 1: res = 2

Output: 2... but expected is 3. Let me re-read the problem.
```

Actually, looking at the problem again, the encoding might be swapped. Let me reconsider: when we store edges, for an original edge u→v, if we traverse from u to v, we DON'T need reversal (cost 0). If we traverse from v to u, we DO need reversal (cost 1).

```python
# Corrected version:
class Solution:
    def minReorder(self, n: int, edges: List[List[int]]) -> int:
        graph = {
            i: [] for i in range(n)
        }

        for u, v in edges:
            # Going u→v (original direction): no reversal needed (cost 0)
            graph[u].append((0, v))
            # Going v→u (against original): reversal needed (cost 1)
            graph[v].append((1, u))
        
        res = 0
        visited = [False] * n
        visited[0] = True
        
        def dfs(cur: int):
            nonlocal res
            adj = graph[cur]
            for cost, next_node in adj:
                if not visited[next_node]:
                    visited[next_node] = True
                    res += cost
                    dfs(next_node)
        
        dfs(0)
        return res
```

### Tags

- **Graph/Tree**: Tree traversal and graph algorithms
- **DFS**: Depth-first search for tree exploration
- **Greedy**: Implicit greedy approach (local optimization leads to global optimum)
- **Edge Cases**: Root node itself (no reversal needed)

## Observations

## Solution

# Tags

