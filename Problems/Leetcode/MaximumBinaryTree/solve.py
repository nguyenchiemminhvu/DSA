from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def constructMaximumBinaryTree(self, nums: List[int]) -> Optional[TreeNode]:
        def build_tree(left:int, right:int) -> Optional[TreeNode]:
            if left > right:
                return None
            max_idx = -1
            max_val = -1
            for i in range(left, right + 1):
                if max_val < nums[i]:
                    max_val = nums[i]
                    max_idx = i
            root = TreeNode(nums[max_idx])
            root.left = build_tree(left, max_idx - 1)
            root.right = build_tree(max_idx + 1, right)
            return root
        return build_tree(0, len(nums) - 1)