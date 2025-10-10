from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isBalanced(self, root: Optional[TreeNode]) -> bool:
        def height(root:Optional[TreeNode]) -> int:
            if root == None:
                return 0
            return 1 + max(height(root.left), height(root.right))
        
        if root == None:
            return True
        if abs(height(root.left) - height(root.right)) > 1:
            return False
        
        check_left = self.isBalanced(root.left)
        check_right = self.isBalanced(root.right)
        return check_left and check_right