from typing import Optional, List

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def increasingBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def inorder(root: Optional[TreeNode], arr: List[int]) -> None:
            if root == None:
                return
            inorder(root.left, arr)
            arr.append(root.val)
            inorder(root.right, arr)
        
        arr = []
        inorder(root, arr)
        dummy = TreeNode()
        cur = dummy
        for val in arr:
            cur.right = TreeNode(val)
            cur = cur.right
        return dummy.right