from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def maxProduct(self, root: Optional[TreeNode]) -> int:
        def sum_tree(root: Optional[TreeNode]) -> int:
            if not root:
                return 0
            return root.val + sum_tree(root.left) + sum_tree(root.right)
        
        def refactor_tree(root: Optional[TreeNode]) -> None:
            if not root:
                return
            refactor_tree(root.left)
            refactor_tree(root.right)
            if root.left:
                root.val += root.left.val
            if root.right:
                root.val += root.right.val
        
        total = sum_tree(root)
        refactor_tree(root)

        max_prod = [0]
        def traversal(root: Optional[TreeNode]) -> None:
            nonlocal total
            if not root:
                return
            cur_sum = root.val
            remain = total - cur_sum
            max_prod[0] = max(max_prod[0], cur_sum * remain)

            traversal(root.left)
            traversal(root.right)
        traversal(root)
        return max_prod[0] % (10**9 + 7)