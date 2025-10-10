from typing import Optional, List

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        def inorder(root: Optional[TreeNode], arr: List[int]) -> None:
            if root == None:
                return
            inorder(root.left, arr)
            arr.append(root.val)
            inorder(root.right, arr)
        
        arr = []
        inorder(root, arr)
        for i in range(1, len(arr)):
            if arr[i] <= arr[i - 1]:
                return False
        return True