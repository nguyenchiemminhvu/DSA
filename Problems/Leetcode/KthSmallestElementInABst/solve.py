from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def kthSmallest(self, root: Optional[TreeNode], k: int) -> int:
        def count(root: Optional[TreeNode]) -> int:
            if not root:
                return 0
            return 1 + count(root.left) + count(root.right)
        
        nleft = count(root.left)
        if nleft == k - 1:
            return root.val
        if nleft > k - 1:
            return self.kthSmallest(root.left, k)
        return self.kthSmallest(root.right, k - nleft - 1)