from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def flatten(self, root: Optional[TreeNode]) -> None:
        """
        Do not return anything, modify root in-place instead.
        """
        def get_predecessor(root: Optional[TreeNode]) -> Optional[TreeNode]:
            if not root or not root.left:
                return root
            p = root.left
            while p and p.right:
                p = p.right
            return p
        
        cur = root
        while cur:
            if cur.left:
                pred = get_predecessor(cur)
                pred.right = cur.right
                cur.right = cur.left
                cur.left = None
            cur = cur.right