from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def longestUnivaluePath(self, root: Optional[TreeNode]) -> int:
        res = 0
        def dfs(root):
            nonlocal res
            if not root:
                return (0, 0)
            
            left = dfs(root.left)
            right = dfs(root.right)
            
            max_left, max_right = 0, 0
            if root.left and root.left.val == root.val:
                max_left = 1 + max(left)
            if root.right and root.right.val == root.val:
                max_right = 1 + max(right)
            res = max(res, max(max_left, max_right))

            if root.left and root.right and root.left.val == root.val and root.right.val == root.val:
                res = max(res, max_left + max_right)
            return (max_left, max_right)
        
        dfs(root)
        return res