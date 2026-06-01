from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def getAllElements(self, root1: Optional[TreeNode], root2: Optional[TreeNode]) -> List[int]:
        def traversal(root: Optional[TreeNode], arr: List[int]):
            if not root:
                return
            traversal(root.left, arr)
            arr.append(root.val)
            traversal(root.right, arr)
        
        arr1 = []
        traversal(root1, arr1)

        arr2 = []
        traversal(root2, arr2)

        return sorted(arr1 + arr2)