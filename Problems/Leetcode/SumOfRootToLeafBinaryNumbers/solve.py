from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def sumRootToLeaf(self, root: Optional[TreeNode]) -> int:
        self.s = 0

        def bin_to_dec(s:str) -> int:
            return 0 if not s else int(s, 2)

        def preorder(root: Optional[TreeNode], temp: str) -> None:
            if root == None:
                return
            if root.left == None and root.right == None:
                self.s += bin_to_dec(temp + str(root.val))
            preorder(root.left, temp + str(root.val))
            preorder(root.right, temp + str(root.val))

        preorder(root, "")
        return self.s