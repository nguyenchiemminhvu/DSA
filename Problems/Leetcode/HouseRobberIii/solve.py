from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def rob(self, root: Optional[TreeNode]) -> int:
        mem = {}
        def F(root: Optional[TreeNode], reach_limit: bool) -> int:
            if not root:
                return 0
            
            if (id(root), reach_limit) in mem:
                return mem[(id(root), reach_limit)]
            
            res = 0
            if reach_limit:
                res = max(
                    res,
                    F(root.left, False) + F(root.right, False)
                )
            else:
                res = max(
                    res,
                    root.val + F(root.left, True) + F(root.right, True),
                    F(root.left, False) + F(root.right, False)
                )
            
            mem[(id(root), reach_limit)] = res
            return res
        
        return F(root, False)