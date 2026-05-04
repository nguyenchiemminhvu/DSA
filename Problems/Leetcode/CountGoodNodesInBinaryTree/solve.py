from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def goodNodes(self, root: TreeNode) -> int:
        count = [0]
        def traversal(root: Optional[TreeNode], prev_max: float):
            if not root:
                return
            if root.val >= prev_max:
                count[0] += 1
            cur_max = max(root.val, prev_max)
            traversal(root.left, cur_max)
            traversal(root.right, cur_max)
        
        traversal(root, float('-inf'))
        return count[0]