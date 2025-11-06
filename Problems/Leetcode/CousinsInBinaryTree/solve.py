from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isCousins(self, root: Optional[TreeNode], x: int, y: int) -> bool:
        self.depth = {}
        self.parent = {}
        
        def inorder(root: Optional[TreeNode], parent: Optional[TreeNode], depth: int) -> None:
            if root == None:
                return
            inorder(root.left, root, depth + 1)
            if root.val == x:
                self.depth[x] = depth
                self.parent[x] = parent
            if root.val == y:
                self.depth[y] = depth
                self.parent[y] = parent
            inorder(root.right, root, depth + 1)
        
        inorder(root, None, 1)
        return self.depth[x] == self.depth[y] and self.parent[x] != self.parent[y]