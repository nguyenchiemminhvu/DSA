from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        mem = {}
        global_max = float('-inf')
        def F(root: Optional[TreeNode]) -> int:
            nonlocal global_max
            if not root:
                return 0
            
            if id(root) in mem:
                return mem[id(root)]

            left_sum = max(F(root.left), 0)
            right_sum = max(F(root.right), 0)
            full_path = left_sum + root.val + right_sum

            global_max = max(
                global_max,
                full_path
            )

            # for parent call, we can only return the child with one branch, choose the max branch
            res = root.val + max(left_sum, right_sum)
            mem[id(root)] = res
            return res
        
        F(root)

        return global_max