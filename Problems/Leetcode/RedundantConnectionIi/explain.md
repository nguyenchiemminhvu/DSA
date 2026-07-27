## Problem

https://leetcode.com/problems/redundant-connection-ii/description/

```
In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.

The given input is a directed graph that started as a rooted tree with n nodes (with distinct values from 1 to n), with one additional directed edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [ui, vi] that represents a directed edge connecting nodes ui and vi, where ui is a parent of child vi.

Return an edge that can be removed so that the resulting graph is a rooted tree of n nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array.

Example 1:

Input: edges = [[1,2],[1,3],[2,3]]
Output: [2,3]

Example 2:

Input: edges = [[1,2],[2,3],[3,4],[4,1],[1,5]]
Output: [4,1]

Constraints:

n == edges.length
3 <= n <= 1000
edges[i].length == 2
1 <= ui, vi <= n
ui != vi
```

## Observations

This problem is an extension of **Redundant Connection I** (undirected graph). The directed nature introduces more complex cases.

In a valid rooted tree of `n` nodes:
- There is **exactly one root** (in-degree 0).
- Every other node has **exactly one parent** (in-degree 1).
- The graph has **no cycles**.

When one extra edge is added, exactly one of the following three cases must occur:

### Case 1: A node gets two parents (in-degree = 2), and there is NO cycle
```
    1
   / \
  2   3
   \ /
    4   ← node 4 has two parents: 2 and 3
```
The extra edge causes a node to have in-degree 2. There is no cycle. The answer is whichever of the two "candidate" edges (both pointing to the double-parent node) appears **last** in the input array.

### Case 2: A node gets two parents (in-degree = 2), and there IS a cycle
```
    1
    |
    2
   / \
  3   |
  |   |
  4 → 2 ← cycle here, and node 2 has two parents: 1 and 4
```
Both a double-parent node exists and there is a cycle. The answer is the candidate edge (pointing to the double-parent node) that is **part of the cycle**. Removing it both fixes the in-degree and breaks the cycle.

### Case 3: No node has two parents, but there IS a cycle
```
1 → 2 → 3 → 4 → 2 (cycle among 2,3,4, no node has in-degree > 1)
```
This is essentially the same as Redundant Connection I. The answer is the last edge in the input array that completes the cycle, found via Union-Find.

## Solution

The solution combines **in-degree tracking** with **Union-Find (Disjoint Set Union)**.

### Step 1: Find the double-parent node (if any)

Scan all edges and track the in-degree of each node. If a node has in-degree 2, record the two candidate edges:
- `cand1`: the **first** edge pointing to that node
- `cand2`: the **second** edge pointing to that node

If no such node exists, we are in **Case 3** — proceed directly with Union-Find on all edges.

### Step 2: Run Union-Find with selective edge skipping

**If a double-parent node exists (Cases 1 & 2)**:
- Try building the tree while **skipping `cand2`** (the last candidate).
- If a cycle is detected (i.e., a Union-Find merge finds both nodes already in the same component), then `cand1` is the answer (Case 2 — `cand2` is in the cycle-free part, so `cand1` must be removed).
- If no cycle is detected, `cand2` is the answer (Case 1 — simply removing the last-occurring duplicate parent edge fixes everything).

**If no double-parent node exists (Case 3)**:
- Run Union-Find on all edges and return the last edge that creates a cycle.

### Pseudocode

```
function findRedundantDirectedConnection(edges):
    find in-degree of all nodes
    cand1, cand2 = None, None
    for each edge [u, v]:
        if in_degree[v] == 2:
            cand1 = first edge pointing to v
            cand2 = second edge pointing to v (= current edge)

    # Union-Find helper: try building tree, skipping 'skip' edge
    function tryBuild(skip):
        init union-find with n nodes
        for each edge [u, v]:
            if edge == skip: continue
            if find(u) == find(v): return False  # cycle found
            union(u, v)
        return True  # no cycle

    if cand2 exists:
        if tryBuild(cand2):
            return cand2   # Case 1: no cycle when cand2 removed
        else:
            return cand1   # Case 2: cycle involves cand1's subtree

    # Case 3: no double-parent, find the cycle edge
    init union-find
    for each edge [u, v]:
        if find(u) == find(v): return [u, v]
        union(u, v)
```

### Complexity

| | Time | Space |
|---|---|---|
| Overall | O(n · α(n)) ≈ O(n) | O(n) |

Where α is the inverse Ackermann function from Union-Find path compression.

## Tags

graph, union-find, disjoint-set
