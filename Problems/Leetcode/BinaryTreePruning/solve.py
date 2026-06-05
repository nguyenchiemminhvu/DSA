from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def dfs(root):
            if not root:
                return None

            left = dfs(root.left)
            right = dfs(root.right)
            if not left and not right:
                if root.val == 0:
                    return None
            root.left = left
            root.right = right
            return root
        
        return dfs(root)