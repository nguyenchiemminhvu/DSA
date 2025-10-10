from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
        def internal_delete(root: Optional[TreeNode], key:int) -> Optional[TreeNode]:
            if root == None:
                return None
            
            if key < root.val:
                root.left = internal_delete(root.left, key)
            elif key > root.val:
                root.right = internal_delete(root.right, key)
            else:
                # leaf node
                if root.left == None and root.right == None:
                    return None
                # one child
                if root.left == None:
                    return root.right
                if root.right == None:
                    return root.left
                # two children
                successor = root.right
                while successor.left != None:
                    successor = successor.left
                root.val = successor.val
                root.right = internal_delete(root.right, successor.val)
            return root
        
        return internal_delete(root, key)