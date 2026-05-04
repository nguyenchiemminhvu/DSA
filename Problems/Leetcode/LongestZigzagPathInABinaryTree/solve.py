from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def longestZigZag(self, root: Optional[TreeNode]) -> int:
        longest = [0]
        
        def traversal(root: Optional[TreeNode], len: int, left: bool):
            if not root:
                return
            
            longest[0] = max(longest[0], len)
            if left:
                traversal(root.left, len + 1, False)
                traversal(root.right, 1, True)
            else:
                traversal(root.left, 1, False)
                traversal(root.right, len + 1, True)
            
        traversal(root, 0, True)
        traversal(root, 0, False)
        return longest[0]
