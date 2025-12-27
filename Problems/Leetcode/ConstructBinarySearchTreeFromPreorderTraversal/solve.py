from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def bstFromPreorder(self, preorder: List[int]) -> Optional[TreeNode]:
        def add_node(root: Optional[TreeNode], val: int) -> Optional[TreeNode]:
            if not root:
                return TreeNode(val)
            if root.val > val:
                root.left = add_node(root.left, val)
            elif root.val < val:
                root.right = add_node(root.right, val)
            return root
        
        root = TreeNode(preorder[0])
        for i in range(1, len(preorder)):
            root = add_node(root, preorder[i])
        return root