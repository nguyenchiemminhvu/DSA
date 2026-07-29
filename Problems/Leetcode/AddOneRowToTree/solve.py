from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def addOneRow(self, root: Optional[TreeNode], val: int, depth: int) -> Optional[TreeNode]:
        if depth == 1:
            new_root = TreeNode(val, root)
            return new_root
        
        def helper(root: Optional[TreeNode], cur_depth: int) -> Optional[TreeNode]:
            if not root:
                if cur_depth == depth:
                    return TreeNode(val)
                return None
            
            if cur_depth == depth - 1:
                left = root.left
                right = root.right
                root.left = TreeNode(val, left)
                root.right = TreeNode(val, None, right)
                root.left.left = left
                root.right.right = right
                return root
            
            root.left = helper(root.left, cur_depth + 1)
            root.right = helper(root.right, cur_depth + 1)
            return root
        
        return helper(root, 1)