from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def delNodes(self, root: Optional[TreeNode], to_delete: List[int]) -> List[TreeNode]:
        res = []

        delete_set = set(to_delete)
        def helper(root: Optional[TreeNode], is_root: bool) -> Optional[TreeNode]:
            if not root:
                return None
            
            is_deleted = root.val in delete_set
            root.left = helper(root.left, is_deleted)
            root.right = helper(root.right, is_deleted)

            if is_root and not is_deleted:
                res.append(root)
            
            if is_deleted:
                return None
            return root

        helper(root, True)
        return res