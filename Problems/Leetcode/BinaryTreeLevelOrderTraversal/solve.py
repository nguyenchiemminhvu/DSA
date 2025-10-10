from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if root == None:
            return []
        
        res = []
        Q = [root]
        while len(Q) > 0:
            cur_len = len(Q)
            row = []
            while cur_len:
                cur_node = Q.pop(0)
                cur_len -= 1
                row.append(cur_node.val)
                if cur_node.left:
                    Q.append(cur_node.left)
                if cur_node.right:
                    Q.append(cur_node.right)
            res.append(row)
        return res