from typing import Optional, List, Dict

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def findMode(self, root: Optional[TreeNode]) -> List[int]:
        def inorder(root: Optional[TreeNode], freq: Dict[int, int]) -> None:
            if root == None:
                return
            inorder(root.left, freq)
            freq[root.val] = freq.get(root.val, 0) + 1
            inorder(root.right, freq)
        
        freq = {}
        inorder(root, freq)
        max_f = max(freq.values())
        return [k for k, v in freq.items() if v == max_f]