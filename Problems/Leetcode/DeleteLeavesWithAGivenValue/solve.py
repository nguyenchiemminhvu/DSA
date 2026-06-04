from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

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