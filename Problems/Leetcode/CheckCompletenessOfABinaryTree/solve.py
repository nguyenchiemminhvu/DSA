from collections import deque
from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isCompleteTree(self, root: Optional[TreeNode]) -> bool:
        q = deque([root])
        level = 0
        found_lack = False
        while q:
            n = 2 ** level
            level += 1
            row = []
            for _ in range(len(q)):
                cur = q.popleft()
                row.append(cur)
                if cur:
                    q.append(cur.left)
                    q.append(cur.right)
            
            # validate row
            if found_lack and row:
                return False
            if len(row) < n:
                found_lack = True
            found_none = False
            for ele in row:
                if found_none and ele != None:
                    return False
                if ele == None:
                    found_none = True
        
        return True