from typing import Optional, List

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def balanceBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def traversal(root: Optional[TreeNode], arr: List[int]) -> None:
            if not root:
                return
            traversal(root.left, arr)
            arr.append(root.val)
            traversal(root.right, arr)
        
        arr = []
        traversal(root, arr)

        def build_tree(left: int, right: int) -> Optional[TreeNode]:
            if left > right:
                return None
            
            mid = left + (right - left) // 2
            root = TreeNode(arr[mid])
            root.left = build_tree(left, mid - 1)
            root.right = build_tree(mid + 1, right)
            return root
        
        return build_tree(0, len(arr) - 1)