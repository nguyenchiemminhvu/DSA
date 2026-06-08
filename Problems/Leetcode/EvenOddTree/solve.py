from collections import deque
from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isEvenOddTree(self, root: Optional[TreeNode]) -> bool:
        q = deque([root])
        idx = -1
        while q:
            idx += 1
            row = []
            z = len(q)
            for _ in range(z):
                cur = q.popleft()
                if idx & 1 and cur.val & 1:
                    return False
                if idx % 2 == 0 and cur.val % 2 == 0:
                    return False
                row.append(cur.val)
                if cur.left:
                    q.append(cur.left)
                if cur.right:
                    q.append(cur.right)
            
            if idx & 1:
                for i in range(1, len(row)):
                    if row[i] >= row[i - 1]:
                        return False
            else:
                for i in range(1, len(row)):
                    if row[i] <= row[i - 1]:
                        return False
        return True