from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def flipEquiv(self, root1: Optional[TreeNode], root2: Optional[TreeNode]) -> bool:
        def check(a: Optional[TreeNode], b: Optional[TreeNode]) -> bool:
            if not a and not b:
                return True
            if a and not b:
                return False
            if not a and b:
                return False
            if a.val != b.val:
                return False
            
            res = False

            # case 1
            res = res or (check(a.left, b.left) and check(a.right, b.right))

            # case 2
            res = res or (check(a.left, b.right) and check(a.right, b.left))
            
            return res
        
        return check(root1, root2)