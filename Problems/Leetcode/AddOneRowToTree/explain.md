## Problem

https://leetcode.com/problems/add-one-row-to-tree/description/

Given the root of a binary tree and two integers `val` and `depth`, add a row of nodes with value `val` at the given depth `depth`. The root node is at depth 1.

**Rules:**
- For each non-null node `cur` at depth `depth - 1`, create two new nodes with value `val` as `cur`'s new left and right children.
- `cur`'s original left subtree becomes the left child of the new left node.
- `cur`'s original right subtree becomes the right child of the new right node.
- If `depth == 1`, create a new root with value `val`, and the original tree becomes its left subtree.

**Examples:**
```
Input: root = [4,2,6,3,1,5], val = 1, depth = 2
Output: [4,1,1,2,null,null,6,3,1,5]

Input: root = [4,2,null,3,1], val = 1, depth = 3
Output: [4,2,null,1,1,3,null,null,1]
```

---

## Observations

- The tree has at most `10^4` nodes, so an O(n) traversal is acceptable.
- The key insight is that insertion happens **one level above** the target depth — we need to reach nodes at `depth - 1` and rewire their children.
- The special case `depth == 1` must be handled separately because there is no parent node to rewire; we simply make a new root.
- When inserting at `depth - 1`, the new left node takes the original left subtree, and the new right node takes the original right subtree. The original subtrees are preserved as grandchildren of the current node.
- A DFS (recursive) traversal naturally tracks current depth, making it a clean fit for this problem.

---

## Solution Explanation

**Step 1 — Handle the base case (`depth == 1`):**  
Create a new node with value `val`, set the entire original tree as its left child, and return it as the new root.

**Step 2 — DFS to depth `depth - 1`:**  
Traverse the tree recursively, carrying the current depth. When we reach a node at `depth - 1`:
- Save its original `left` and `right` children.
- Replace `left` with a new node(`val`) whose left child is the saved original left.
- Replace `right` with a new node(`val`) whose right child is the saved original right.

**Step 3 — Handle null nodes:**  
If we reach a `null` node but haven't yet reached `depth`, simply return `None`. This avoids unnecessary work on missing branches.

**Complexity:**
- Time: O(n) — each node is visited at most once.
- Space: O(h) — recursion stack, where h is the height of the tree (O(log n) balanced, O(n) worst case).

---

## Solution

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def addOneRow(self, root: Optional[TreeNode], val: int, depth: int) -> Optional[TreeNode]:
        if depth == 1:
            new_root = TreeNode(val, root)
            return new_root
        
        def helper(root: Optional[TreeNode], cur_depth: int) -> Optional[TreeNode]:
            if not root:
                return None
            
            if cur_depth == depth - 1:
                left = root.left
                right = root.right
                root.left = TreeNode(val, left)
                root.right = TreeNode(val, None, right)
                return root
            
            root.left = helper(root.left, cur_depth + 1)
            root.right = helper(root.right, cur_depth + 1)
            return root
        
        return helper(root, 1)
```
