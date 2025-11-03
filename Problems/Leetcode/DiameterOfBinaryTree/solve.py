from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        self.memo = {}
        def height(root: Optional[TreeNode]) -> int:
            if root in self.memo:
                return self.memo[root]
            h = 0 if root == None else 1 + max(height(root.left), height(root.right))
            self.memo[root] = h
            return h
        
        self.res = 0
        def preorder(root: Optional[TreeNode]) -> None:
            if root == None:
                return
            self.res = max(self.res, self.memo[root.left] + self.memo[root.right])
            preorder(root.left)
            preorder(root.right)

        h = height(root)
        preorder(root)
        return self.res