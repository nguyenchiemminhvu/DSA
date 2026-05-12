from typing import List, Optional
from collections import deque

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def zigzagLevelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root:
            return []
        
        def bfs() -> List[List[int]]:
            rows = []
            rev = False
            q = deque([root])
            while q:
                size = len(q)
                row = []
                for _ in range(size):
                    cur = q.popleft()
                    row.append(cur.val)
                    if cur.left:
                        q.append(cur.left)
                    if cur.right:
                        q.append(cur.right)
                if rev:
                    row.reverse()
                rows.append(row)
                rev = not rev
            return rows
        
        return bfs()