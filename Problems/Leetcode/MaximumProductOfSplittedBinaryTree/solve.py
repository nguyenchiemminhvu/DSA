from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def maxProduct(self, root: Optional[TreeNode]) -> int:
        total = 0
        res = 0

        def traversal(root: Optional[TreeNode]) -> None:
            nonlocal total
            if not root:
                return
            traversal(root.left)
            total += root.val
            traversal(root.right)

            if root.left:
                root.val += root.left.val
            if root.right:
                root.val += root.right.val
        
        def traversal_2(root: Optional[TreeNode]) -> None:
            nonlocal total, res
            if not root:
                return
            res = max(res, (total - root.val) * root.val)
            traversal_2(root.left)
            traversal_2(root.right)
        
        traversal(root)
        traversal_2(root)
        return res % (10**9 + 7)