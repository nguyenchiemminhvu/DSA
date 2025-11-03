from typing import Optional, Set

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def findTarget(self, root: Optional[TreeNode], k: int) -> bool:
        def inorder(root: Optional[TreeNode], d: Set[int]) -> bool:
            if root == None:
                return False
            if k - root.val in d:
                return True
            d.add(root.val)
            if inorder(root.left, d):
                return True
            if inorder(root.right, d):
                return True
            return False
        
        s = set()
        return inorder(root, s)