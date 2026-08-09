## Problem

https://leetcode.com/problems/weighted-sum-of-a-tree/description/

Given a rooted tree of `n` nodes (labeled `0` to `n-1`, rooted at `0`) represented by a `parent` array and a `nums` array, compute the **weighted sum** of all nodes.

The **weight** of node `i` at depth `d` is:

$$\text{weight}(i) = \text{nums}[i] \times (h - d + 1)$$

where $h$ is the **height** of the tree (maximum depth among all nodes), and depth is 1-indexed (root has depth 1).

Return the sum of weights of all nodes.

**Example 1:**
```
parent = [-1,0,0,0,2,2], nums = [5,2,3,1,4,6]
Tree height h = 3
Node 0: 5*(3-1+1)=15, Node 1: 2*(3-2+1)=4, Node 2: 3*(3-2+1)=6
Node 3: 1*(3-2+1)=2, Node 4: 4*(3-3+1)=4, Node 5: 6*(3-3+1)=6
Output: 37
```

**Example 2:**
```
parent = [-1,0,1,2], nums = [1,2,3,4]  (a chain)
Tree height h = 4
Output: 20
```

---

## Observations

- The multiplier `(h - d + 1)` is largest at the root (depth 1) and smallest at the deepest leaves (depth h, multiplier = 1). Deeper nodes are weighted less.
- The height `h` must be known before computing any weight, so a pre-pass to find `h` is necessary.
- Building an **adjacency list** (children list) from the `parent` array allows straightforward DFS from the root.
- Since depth increases by 1 at each level, it can be threaded through the recursion without extra storage.
- The weight formula is just a linear combination of `nums[i]`, so nothing needs to be stored — values can be accumulated directly during DFS.

---

## Solution Explanation

```python
class Solution:
    def weightedSum(self, parent: list[int], nums: list[int]) -> int:
        graph = defaultdict(list)
        for u, p in enumerate(parent):
            graph[p].append(u)

        def height(node: int) -> int:
            h = 1
            for adj in graph[node]:
                h = max(h, 1 + height(adj))
            return h

        h = height(0)

        def dfs(node: int, d: int) -> int:
            nonlocal h
            val = nums[node] * (h - d + 1)
            for adj in graph[node]:
                val += dfs(adj, d + 1)
            return val
        
        return dfs(0, 1)
```

**Step 1 — Build the children graph:**  
Iterate over `parent`, appending each node `u` to its parent's child list. Node `0` (root) gets appended under key `-1`, which is never traversed.

**Step 2 — Compute tree height:**  
`height(node)` recursively returns the maximum depth reachable from `node`. At each node it takes `1 + max(height(child))` over all children, with a base of `1` for leaves.

**Step 3 — DFS with weighted accumulation:**  
`dfs(node, d)` computes the contribution of the entire subtree rooted at `node`. It:
1. Computes `nums[node] * (h - d + 1)` for the current node.
2. Recurses into each child with depth `d + 1`, adding their subtree sums.

Starting at `dfs(0, 1)` covers the entire tree.

**Complexity:**
- Time: $O(n)$ for both the height pass and the DFS pass.
- Space: $O(n)$ for the adjacency list and $O(h)$ recursion stack depth.
