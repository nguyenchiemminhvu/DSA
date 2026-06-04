from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def constructFromPrePost(self, preorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
        def build_tree(pre_left, pre_right, post_left, post_right):
            if pre_left > pre_right or post_left > post_right:
                return None
            if pre_left == pre_right:
                return TreeNode(preorder[pre_left])
            
            root = TreeNode(preorder[pre_left])
            next_pre_left = pre_left + 1
            next_post_left = postorder.index(preorder[next_pre_left])

            size_next_post_left = next_post_left - post_left + 1
            size_next_post_right = post_right - 1 - next_post_left

            root.left = build_tree(next_pre_left, next_pre_left + size_next_post_left - 1, post_left, next_post_left)
            root.right = build_tree(next_pre_left + size_next_post_left, pre_right, next_post_left + 1, post_right - 1)

            return root
        
        return build_tree(0, len(preorder) - 1, 0, len(postorder) - 1)