from typing import List, Optional
from collections import defaultdict

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def findDuplicateSubtrees(self, root: Optional[TreeNode]) -> List[Optional[TreeNode]]:
        if root == None:
            return []
        
        counter = defaultdict(int)
        duplicated_trees = []
        def dfs(root: Optional[TreeNode]) -> str:
            if root == None:
                return '#'
            temp = str(root.val) + "," + dfs(root.left) + "," + dfs(root.right)
            counter[temp] += 1
            if (counter[temp] == 2):
                duplicated_trees.append(root)
            return temp

        dfs(root)
        return duplicated_trees