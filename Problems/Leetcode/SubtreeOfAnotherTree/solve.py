from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:
        def is_same_tree(a: Optional[TreeNode], b: Optional[TreeNode]) -> bool:
            if a == None and b == None:
                return True
            if a == None and b != None:
                return False
            if a != None and b == None:
                return False
            if a.val != b.val:
                return False
            return is_same_tree(a.left, b.left) and is_same_tree(a.right, b.right)
        
        if subRoot == None:
            return True
        if root == None:
            return False
        if root.val == subRoot.val:
            if is_same_tree(root, subRoot):
                return True
        return self.isSubtree(root.left, subRoot) or self.isSubtree(root.right, subRoot)