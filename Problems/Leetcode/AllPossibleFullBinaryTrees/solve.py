from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def allPossibleFBT(self, n: int) -> List[Optional[TreeNode]]:
        if n % 2 == 0:
            return []
        
        def build_trees(n: int) -> List[Optional[TreeNode]]:
            if n <= 0:
                return [None]
            if n == 1:
                return [TreeNode(0)]
            
            trees = []
            n -= 1
            for count_left in range(1, n, 2):
                left_trees = build_trees(count_left)
                count_right = n - count_left
                right_trees = build_trees(count_right)
                for node_left in left_trees:
                    for node_right in right_trees:
                        root = TreeNode(0)
                        root.left = node_left
                        root.right = node_right
                        trees.append(root)
            return trees
        
        return build_trees(n)