from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def pathSum(self, root: Optional[TreeNode], target: int) -> List[List[int]]:
        res = []        
        def traversal(root: Optional[TreeNode], cur_sum: int, tmp: List[int]) -> None:
            if not root:
                return
            if not root.left and not root.right:
                if cur_sum + root.val == target:
                    res.append(tmp + [root.val])
                return
            traversal(root.left, cur_sum + root.val, tmp + [root.val])
            traversal(root.right, cur_sum + root.val, tmp + [root.val])
        
        traversal(root, 0, [])
        return res