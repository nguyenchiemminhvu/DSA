from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def sumOfLeftLeaves(self, root: Optional[TreeNode]) -> int:
        s = []
        def traversal(root: Optional[TreeNode], went_left:bool) -> None:
            if root == None:
                return
            if went_left and root.left == None and root.right == None:
                s.append(root.val)
            traversal(root.left, True)
            traversal(root.right, False)
        traversal(root, False)
        return sum(s)