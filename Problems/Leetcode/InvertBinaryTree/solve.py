from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def build_invert_tree(root: Optional[TreeNode], i_root: Optional[TreeNode]):
            if root == None:
                return None
            i_root = TreeNode(root.val)
            i_root.right = build_invert_tree(root.left, i_root.right)
            i_root.left = build_invert_tree(root.right, i_root.left)
            return i_root
        
        new_root = None
        new_root = build_invert_tree(root, new_root)
        return new_root