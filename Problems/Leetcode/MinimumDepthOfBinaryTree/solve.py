from collections import deque
from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def minDepth(self, root: Optional[TreeNode]) -> int:
        if root == None:
            return 0
        level = 1
        q = deque([root])
        while len(q) > 0:
            cur_len = len(q)
            while cur_len > 0:
                cur_node = q.popleft()
                cur_len -= 1
                if cur_node.left == None and cur_node.right == None:
                    return level
                if cur_node.left:
                    q.append(cur_node.left)
                if cur_node.right:
                    q.append(cur_node.right)
            level += 1
        return level