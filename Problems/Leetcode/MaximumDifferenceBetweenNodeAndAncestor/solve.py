from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def maxAncestorDiff(self, root: Optional[TreeNode]) -> int:
        res = 0
        def dfs(root):
            nonlocal res
            if not root:
                return (float('inf'), float('-inf')) # min, max
            
            mi_left, ma_left = dfs(root.left)
            mi_right, ma_right = dfs(root.right)
            res = max(
                res,
                abs(root.val - mi_left) if mi_left != float('inf') else 0,
                abs(root.val - ma_left) if ma_left != float('-inf') else 0,
                abs(root.val - mi_right) if mi_right != float('inf') else 0,
                abs(root.val - ma_right) if ma_right != float('-inf') else 0
            )

            mi = min(mi_left, mi_right, root.val)
            ma = max(ma_left, ma_right, root.val)
            return (mi, ma)
        
        dfs(root)
        return res
