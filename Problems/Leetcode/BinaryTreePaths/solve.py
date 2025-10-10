from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def binaryTreePaths(self, root: Optional[TreeNode]) -> List[str]:
        def traversal(root: Optional[TreeNode], path: List[int], paths: List[List[int]]) -> None:
            if root == None:
                return
            path.append(root.val)
            if root.left == None and root.right == None:
                paths.append([val for val in path])
            traversal(root.left, path, paths)
            traversal(root.right, path, paths)
            path.pop()
        
        temp = []
        paths = []
        traversal(root, temp, paths)
        return ["->".join([str(val) for val in p]) for p in paths]