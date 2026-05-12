from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        res = [0]
        def dfs(root: Optional[TreeNode], s: str):
            if not root:
                return
            
            if not root.left and not root.right:
                res[0] += int(s + str(root.val))
                return
            
            dfs(root.left, s + str(root.val))
            dfs(root.right, s + str(root.val))
        
        dfs(root, '')
        return res[0]