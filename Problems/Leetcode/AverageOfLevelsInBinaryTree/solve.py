from collections import deque
from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def averageOfLevels(self, root: Optional[TreeNode]) -> List[float]:
        rows = []
        if root == None:
            return rows

        q = deque([root])
        while q:
            cur_len = len(q)
            row_val = 0.0
            row_count = 0
            while cur_len:
                cur_node = q.popleft()
                cur_len -= 1

                row_val += cur_node.val
                row_count += 1

                if cur_node.left:
                    q.append(cur_node.left)
                if cur_node.right:
                    q.append(cur_node.right)
            
            rows.append(row_val / row_count)
        
        return rows