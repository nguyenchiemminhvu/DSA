from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def reverseOddLevels(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def dfs(left: Optional[TreeNode], right: Optional[TreeNode], level: int):
            if not left:
                return right
            if not right:
                return left
            
            if level & 1:
                left.val, right.val = right.val, left.val
            
            dfs(left.left, right.right, level + 1)
            dfs(left.right, right.left, level + 1)
        
        dfs(root.left, root.right, 1)
        return root