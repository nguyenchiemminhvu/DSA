from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def findTilt(self, root: Optional[TreeNode]) -> int:
        def build_sum_tree(root: Optional[TreeNode]) -> None:
            if root == None:
                return

            build_sum_tree(root.left)
            build_sum_tree(root.right)

            sleft = root.left.val if root.left else 0
            sright = root.right.val if root.right else 0
            root.val += sleft + sright

        def build_tilt_tree(root: Optional[TreeNode]) -> None:
            if root == None:
                return

            sleft = root.left.val if root.left else 0
            sright = root.right.val if root.right else 0
            root.val = abs(sleft - sright)

            build_tilt_tree(root.left)
            build_tilt_tree(root.right)

            return root
        
        build_sum_tree(root)
        root = build_tilt_tree(root)
        build_sum_tree(root)
        return root.val if root else 0