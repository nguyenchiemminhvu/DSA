from typing import Optional, Set

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def findSecondMinimumValue(self, root: Optional[TreeNode]) -> int:
        def inorder(root: Optional[TreeNode], arr: Set[int]) -> None:
            if root == None:
                return
            inorder(root.left, arr)
            arr.add(root.val)
            inorder(root.right, arr)
        
        arr = set()
        inorder(root, arr)
        return -1 if len(arr) <= 1 else sorted(list(arr))[1]