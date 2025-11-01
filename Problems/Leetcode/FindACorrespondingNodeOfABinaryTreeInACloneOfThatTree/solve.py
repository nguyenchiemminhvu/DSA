# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def getTargetCopy(self, root_a: TreeNode, root_b: TreeNode, target: TreeNode) -> TreeNode:
        if root_a == None:
            return None
        if root_a == target:
            return root_b
        left = self.getTargetCopy(root_a.left, root_b.left, target)
        if left != None:
            return left
        right = self.getTargetCopy(root_a.right, root_b.right, target)
        if right != None:
            return right
        return None