## Problem

https://leetcode.com/problems/delete-leaves-with-a-given-value/description/

Given a binary tree `root` and an integer `target`, delete all the leaf nodes with value `target`.

Once a leaf node with value `target` is deleted, if its parent becomes a new leaf node with value `target`, it must also be deleted. Repeat this process until no such leaf exists.

**Example 1:**
```
Input: root = [1,2,3,2,null,2,4], target = 2
Output: [1,null,3,null,4]
```

**Example 2:**
```
Input: root = [1,3,3,3,2], target = 3
Output: [1,3,null,null,2]
```

**Example 3:**
```
Input: root = [1,2,null,2,null,2], target = 2
Output: [1]
```

**Constraints:**
- The number of nodes in the tree is in the range `[1, 3000]`.
- `1 <= Node.val, target <= 1000`

---

## Observations

- A node is a **leaf** if and only if both its left and right children are `None`.
- The deletion is **cascading**: removing a leaf can expose its parent as a new leaf that may also need to be removed.
- The cascade naturally fits a **post-order traversal** (left → right → root):
  - Process children first, then decide whether the current node should be removed.
  - By the time we evaluate a node, its subtrees have already been cleaned up.
- If after processing both subtrees a node has no children (`left == None` and `right == None`) and its value equals `target`, we delete it by returning `None` to the parent.
- The root itself can be deleted if it ends up being a lone leaf with value `target`.

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
    def removeLeafNodes(self, root: Optional[TreeNode], target: int) -> Optional[TreeNode]:
        def dfs(root, target):
            if not root:
                return None
            
            left = dfs(root.left, target)
            right = dfs(root.right, target)
            if not left and not right and root.val == target:
                return None
            root.left = left
            root.right = right
            return root
        
        return dfs(root, target)
```

**Step-by-step walkthrough:**

1. **Base case:** If `root` is `None`, return `None` — nothing to process.
2. **Recurse left and right:** Call `dfs` on both children first (post-order). The returned values are the *updated* subtree roots after deletions have been applied.
3. **Leaf check after cleanup:** After recursion, `left` and `right` hold the cleaned subtrees. If both are `None` (current node is now a leaf) and `root.val == target`, return `None` — this node is deleted.
4. **Reattach subtrees:** Otherwise, reattach the cleaned subtrees (`root.left = left`, `root.right = right`) and return the current node as-is.
5. **Result:** `dfs(root, target)` returns the new root of the tree, which may be `None` if the entire tree was deleted.

**Why post-order works perfectly here:**  
The cascading deletion is handled implicitly. When a child is deleted and returns `None`, the parent's `left` or `right` becomes `None`. If that makes the parent a new leaf with value `target`, the parent is then deleted in the same traversal pass — no need for multiple passes.

**Complexity:**
- **Time:** $O(N)$ — every node is visited exactly once.
- **Space:** $O(H)$ — recursion stack depth, where $H$ is the height of the tree ($O(\log N)$ for balanced, $O(N)$ worst case for skewed).
