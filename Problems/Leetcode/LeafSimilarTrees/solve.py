from typing import Optional, List

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def leafSimilar(self, root1: Optional[TreeNode], root2: Optional[TreeNode]) -> bool:
        def postorder(root: Optional[TreeNode], arr: List[int]) -> None:
            if root == None:
                return
            postorder(root.left, arr)
            postorder(root.right, arr)
            if root.left == None and root.right == None:
                arr.append(root.val)
        
        arr1 = []
        postorder(root1, arr1)
        arr2 = []
        postorder(root2, arr2)
        return arr1 == arr2