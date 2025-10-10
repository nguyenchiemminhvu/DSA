from typing import List

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        def build_path(root: 'TreeNode', target: 'TreeNode', path: List['TreeNode']) -> bool:
            if root == None:
                return False
            
            path.append(root)
            if root == target:
                return True
            
            if build_path(root.left, target, path) or build_path(root.right, target, path):
                return True
            
            path.pop()
            return False

        path_p = []
        build_path(root, p, path_p)

        path_q = []
        build_path(root, q, path_q)

        ip = 0
        iq = 0
        while ip < len(path_p) and iq < len(path_q) and path_p[ip] == path_q[iq]:
            ip += 1
            iq += 1
        return path_p[ip - 1]