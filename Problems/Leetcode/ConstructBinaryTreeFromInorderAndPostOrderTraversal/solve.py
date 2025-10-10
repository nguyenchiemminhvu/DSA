from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def buildTree(self, inorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
        if len(postorder) <= 0:
            return None
        
        root_value = postorder[-1]
        root_idx = inorder.index(root_value)
        inorder_left = inorder[:root_idx]
        inorder_right = inorder[root_idx + 1:]
        postorder_left = postorder[:len(inorder_left)]
        postorder_right = postorder[len(inorder_left):len(postorder) - 1]

        root = TreeNode(root_value)
        root.left = self.buildTree(inorder_left, postorder_left)
        root.right = self.buildTree(inorder_right, postorder_right)
        return root