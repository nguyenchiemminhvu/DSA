## Problem

https://leetcode.com/problems/binary-tree-pruning/description/

Given the root of a binary tree where every node value is `0` or `1`, return the same tree after removing every subtree that does **not** contain a `1`.

A subtree of a node is the node itself plus all of its descendants.

---

## Observations

1. **A leaf node with value `0` should be removed** — it contains no `1`, so it satisfies the pruning condition immediately.
2. **Bottom-up processing is essential** — to decide whether a node should stay, we must first know whether its children contain a `1`. This naturally leads to a **post-order DFS** (process left → right → current).
3. **A node can be kept if**:
   - Its value is `1`, **or**
   - At least one of its children (after pruning) is non-null (meaning that subtree contained a `1`).
4. **A node should be removed (return `None`) if**:
   - Both its pruned left and right children are `None`, **and**
   - Its own value is `0`.
5. The problem is **self-similar** — pruning a tree is the same as pruning its left subtree, pruning its right subtree, then deciding what to do with the root. This is the classic recursive substructure.

---

## Solution Explanation

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def dfs(root):
            if not root:
                return None

            left = dfs(root.left)
            right = dfs(root.right)
            if not left and not right:
                if root.val == 0:
                    return None
            root.left = left
            root.right = right
            return root
        
        return dfs(root)
```

### Step-by-step

1. **Base case**: If the current node is `None`, return `None` — nothing to prune.
2. **Recurse left and right first** (post-order):
   - `left = dfs(root.left)` — prune the entire left subtree; returns the new left child (or `None` if it was fully pruned).
   - `right = dfs(root.right)` — same for the right subtree.
3. **Pruning decision** at the current node:
   - If both `left` and `right` came back as `None`, the current node has no children containing a `1`.
   - If additionally `root.val == 0`, the current node itself has no `1` — so the entire subtree rooted here contains no `1`. Return `None` to remove it.
4. **Otherwise**, update the node's children to the pruned versions and **return the node** — it is part of the result tree.

### Why this works

The recursion guarantees that by the time we inspect a node, its children have already been reduced to only the parts that contain a `1`. So the check `not left and not right and root.val == 0` is a complete test: no descendants hold a `1`, and the node itself doesn't either.

### Complexity

| | |
|---|---|
| **Time** | $O(n)$ — every node is visited exactly once |
| **Space** | $O(h)$ — recursion stack depth equals the tree height $h$; $O(\log n)$ for balanced, $O(n)$ worst case |
