from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        prefix_sum = 0
        def dfs(root):
            nonlocal prefix_sum
            if not root:
                return
            dfs(root.right)
            prefix_sum += root.val
            root.val = prefix_sum
            dfs(root.left)
            
        
        dfs(root)
        return root