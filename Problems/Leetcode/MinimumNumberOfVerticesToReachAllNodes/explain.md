## Problem

https://leetcode.com/problems/minimum-number-of-vertices-to-reach-all-nodes/description/

```
Given a directed acyclic graph, with n vertices numbered from 0 to n-1, and an array edges where
edges[i] = [fromi, toi] represents a directed edge from node fromi to node toi.

Find the smallest set of vertices from which all nodes in the graph are reachable. It's guaranteed
that a unique solution exists.

Notice that you can return the vertices in any order.

Example 1:

Input: n = 6, edges = [[0,1],[0,2],[2,5],[3,4],[4,2]]
Output: [0,3]
Explanation: It's not possible to reach all the nodes from a single vertex.
From 0 we can reach [0,1,2,5]. From 3 we can reach [3,4,2,5]. So we output [0,3].

Example 2:

Input: n = 5, edges = [[0,1],[2,1],[3,1],[1,4],[2,4]]
Output: [0,2,3]
Explanation: Notice that vertices 0, 3 and 2 are not reachable from any other node, so we must
include them. Also any of these vertices can reach nodes 1 and 4.

Constraints:

2 <= n <= 10^5
1 <= edges.length <= min(10^5, n * (n - 1) / 2)
edges[i].length == 2
0 <= fromi, toi < n
All pairs (fromi, toi) are distinct.
```

## Observations

1. **In-degree is the key**: In a DAG, every edge `[u, v]` means node `v` is reachable from node `u`. A node with **in-degree > 0** already has at least one parent that can reach it, so it does **not** need to be in the answer set.

2. **Nodes with in-degree = 0 must be included**: If a node has no incoming edges, no other node in the graph can reach it. Therefore, it **must** be a starting vertex in any valid answer set.

3. **DAG guarantee ensures full coverage**: Because the graph is acyclic, following edges from every in-degree-0 node will eventually cover all other nodes (each node with in-degree > 0 traces back through parents to some in-degree-0 ancestor).

4. **The problem reduces to**: Find all nodes that never appear as a destination in any edge — i.e., all nodes with in-degree = 0.

## Solution

```python
class Solution:
    def findSmallestSetOfVertices(self, n: int, edges: List[List[int]]) -> List[int]:
        res = []
        mp = defaultdict(int)
        for u, v in edges:
            mp[v] += 1
        for i in range(n):
            if i not in mp:
                res.append(i)
        return res
```

### Step-by-step breakdown

**Step 1 — Track all nodes that have incoming edges:**
```python
mp = defaultdict(int)
for u, v in edges:
    mp[v] += 1
```
For every edge `[u, v]`, node `v` receives an incoming edge. We record it in `mp`. After this loop, `mp` contains every node that is reachable from some other node.

**Step 2 — Collect nodes with no incoming edges:**
```python
for i in range(n):
    if i not in mp:
        res.append(i)
```
Any node `i` not present in `mp` has in-degree 0 — nothing points to it. These are the only nodes we need in our answer.

### Example Walkthrough

**Example 1**: `n = 6`, `edges = [[0,1],[0,2],[2,5],[3,4],[4,2]]`

| Edge  | Destination recorded in `mp` |
|-------|------------------------------|
| [0,1] | mp[1] = 1                    |
| [0,2] | mp[2] = 1                    |
| [2,5] | mp[5] = 1                    |
| [3,4] | mp[4] = 1                    |
| [4,2] | mp[2] = 2                    |

Nodes in `mp` (have incoming edges): `{1, 2, 4, 5}`  
Nodes **not** in `mp` (in-degree = 0): **0, 3** → Output: `[0, 3]` ✓

**Example 2**: `n = 5`, `edges = [[0,1],[2,1],[3,1],[1,4],[2,4]]`

Nodes in `mp` (have incoming edges): `{1, 4}`  
Nodes **not** in `mp` (in-degree = 0): **0, 2, 3** → Output: `[0, 2, 3]` ✓

### Why this is the minimum set

- Every node with in-degree = 0 **must** be included (nothing else can reach it).
- Every node with in-degree > 0 **can be excluded** (it is reachable from its parent, which traces back to some in-degree-0 ancestor).
- Therefore, the set of all in-degree-0 nodes is both necessary and sufficient — it is exactly the minimum set.

## Complexity

| | Complexity |
|-|------------|
| **Time** | $O(n + E)$ — one pass over edges to build `mp`, one pass over `n` nodes to collect the answer |
| **Space** | $O(n)$ — the `mp` dictionary holds at most `n` entries |

## Tags

graph, DAG, in-degree
