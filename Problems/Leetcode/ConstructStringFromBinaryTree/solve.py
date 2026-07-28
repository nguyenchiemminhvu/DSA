from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def tree2str(self, root: Optional[TreeNode]) -> str:
        def build_str(root: Optional[TreeNode]) -> str:
            if not root:
                return ''
            
            cur = str(root.val)
            left = build_str(root.left)
            right = build_str(root.right)

            if left and right:
                cur += '(' + left + ')'
                cur += '(' + right + ')'
            elif not left and right:
                cur += '(' + left + ')'
                cur += '(' + right + ')'
            elif left and not right:
                cur += '(' + left + ')'
            return cur
        
        s = build_str(root)
        return s