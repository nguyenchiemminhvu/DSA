# Count the Number of Good Nodes (LeetCode 2049)

## Problem

https://leetcode.com/problems/count-the-number-of-good-nodes/description/

There is an undirected tree with `n` nodes labeled from `0` to `n - 1`, and rooted at node `0`. You are given a 2D integer array `edges` of length `n - 1`, where `edges[i] = [ai, bi]` indicates that there is an edge between nodes `ai` and `bi` in the tree.

A node is **good** if all the subtrees rooted at its children have the **same size**.

Return the number of good nodes in the given tree.

> A subtree of `treeName` is a tree consisting of a node in `treeName` and all of its descendants.

### Examples

**Example 1:**
```
Input: edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]
Output: 7

Explanation: All of the nodes of the given tree are good.
```

**Example 2:**
```
Input: edges = [[0,1],[1,2],[2,3],[3,4],[0,5],[1,6],[2,7],[3,8]]
Output: 6

Explanation: There are 6 good nodes in the given tree.
```

**Example 3:**
```
Input: edges = [[0,1],[1,2],[1,3],[1,4],[0,5],[5,6],[6,7],[7,8],[0,9],[9,10],[9,12],[10,11]]
Output: 12

Explanation: All nodes except node 9 are good.
```

### Constraints
- `2 <= n <= 10^5`
- `edges.length == n - 1`
- `edges[i].length == 2`
- `0 <= ai, bi < n`
- The input is generated such that `edges` represents a valid tree.

## Observations

### 1. **Tree Rooted at Node 0**
The input is an undirected edge list. To do a rooted DFS from node `0`, we build an adjacency list and track the parent node to avoid revisiting it (since the graph is undirected).

### 2. **Subtree Size is the Key Value**
For each node, we need to know the size of every child's subtree. A DFS naturally computes subtree sizes bottom-up: a leaf returns size `1`, and an internal node returns `1 + sum(child subtree sizes)`.

### 3. **Good Node Condition**
A node is good if **all children subtree sizes are equal**. Special cases:
- A **leaf node** has no children → trivially good (vacuously true).
- A node with one child is always good (only one subtree size to compare).
- A node with multiple children must have all subtree sizes identical.

### 4. **DFS Bottom-Up is the Natural Fit**
Because a node's goodness depends on its children's subtree sizes, we must process children before the parent. Post-order DFS handles this automatically.

### 5. **Counting During Traversal**
We can maintain a global (or `nonlocal`) counter incremented whenever a node qualifies as good, avoiding the need for a separate pass over results.

## Solution

### Approach: DFS (Post-order, Bottom-Up)

**Algorithm:**

1. Build an adjacency list from `edges`.
2. Run DFS from node `0` with parent tracking to avoid cycles.
3. For each node, collect the subtree sizes of all children.
4. If all children sizes are equal (or there are no children), increment the good-node counter.
5. Return `1 + sum(child sizes)` as the current subtree size.

### Step-by-Step Walkthrough

```
edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]

Tree structure:
        0
       / \
      1   2
     / \ / \
    3  4 5  6

DFS(0, -1):
  DFS(1, 0):
    DFS(3, 1) → leaf, size=1, good (no children) → res=1
    DFS(4, 1) → leaf, size=1, good (no children) → res=2
    children sizes = [1, 1] → all equal → node 1 is good → res=3
    return 3
  DFS(2, 0):
    DFS(5, 2) → leaf, size=1, good → res=4
    DFS(6, 2) → leaf, size=1, good → res=5
    children sizes = [1, 1] → all equal → node 2 is good → res=6
    return 3
  children sizes = [3, 3] → all equal → node 0 is good → res=7
  return 7

Answer: 7
```

### Code Implementation

```python
from collections import defaultdict
from typing import List

class Solution:
    def countGoodNodes(self, edges: List[List[int]]) -> int:
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        res = 0

        def dfs(node, parent):
            nonlocal res
            if not graph[node]:
                res += 1   # leaf node is trivially good
                return 1

            total = 1
            child_sizes = []
            for adj in graph[node]:
                if adj == parent:
                    continue
                size = dfs(adj, node)
                total += size
                child_sizes.append(size)

            # Good if all child subtree sizes are the same
            if not child_sizes or all(s == child_sizes[0] for s in child_sizes):
                res += 1

            return total

        dfs(0, -1)
        return res
```

### Complexity Analysis

**Time Complexity: O(n)**
- Each node is visited exactly once during DFS.
- The `all(...)` check over children is amortized O(n) total across the whole tree (each edge is examined once per direction).

**Space Complexity: O(n)**
- Adjacency list: O(n) (tree has n-1 edges).
- Recursion stack depth: O(n) in the worst case (skewed/path tree).
- `child_sizes` array per call: O(degree), totalling O(n) across all calls.

### Edge Cases

1. **Two-node tree** (`n = 2`): Both nodes are good — root has one child (trivially good), child is a leaf (trivially good).
2. **Path graph** (every node has one child): Every node is good since each has at most one child.
3. **Star graph** (root connected to all others): Root is good (all children are leaves of size 1); all leaves are good.
4. **Unbalanced tree**: Only nodes whose children have equal subtree sizes count.

### Key Insights

- **Leaf nodes are always good** — with zero children the condition holds vacuously.
- **Post-order DFS** is the simplest way to compute subtree sizes and check the good-node condition in a single pass.
- **Parent tracking** (instead of a `visited` set) is sufficient and more memory-efficient for trees.

# Tags

Tree, DFS, Post-order Traversal, Subtree Size, Recursion

