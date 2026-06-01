from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def sumEvenGrandparent(self, root: Optional[TreeNode]) -> int:
        def dfs(root, parent, grandparent) -> int:
            if not root:
                return 0
            
            res = 0
            if grandparent and grandparent.val % 2 == 0:
                res += root.val

            res += dfs(root.left, root, parent)
            res += dfs(root.right, root, parent)
            return res
        
        return dfs(root, None, None)