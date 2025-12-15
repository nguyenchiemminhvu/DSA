from typing import Optional, List

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def smallestFromLeaf(self, root: Optional[TreeNode]) -> str:
        arr = []
        def traversal(root: Optional[TreeNode], tmp: List[str]) -> None:
            if not root:
                return
            if not root.left and not root.right:
                s = "".join([chr(root.val + ord('a'))] + [chr(val + ord('a')) for val in tmp])
                arr.append(s)
                return
            
            traversal(root.left, [root.val] + tmp)
            traversal(root.right, [root.val] + tmp)
        
        traversal(root, [])
        return min(arr)