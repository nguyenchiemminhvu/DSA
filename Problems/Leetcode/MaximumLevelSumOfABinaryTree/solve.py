from typing import Optional
from collections import deque

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def maxLevelSum(self, root: Optional[TreeNode]) -> int:
        def bfs() -> int:
            max_level = 0
            cur_level = 0
            max_sum = float('-inf')
            q = deque([root])
            while q:
                cur_level += 1
                cur_sum = 0
                size = len(q)
                for _ in range(size):
                    cur_node = q.pop()
                    cur_sum += cur_node.val
                    if cur_node.left:
                        q.appendleft(cur_node.left)
                    if cur_node.right:
                        q.appendleft(cur_node.right)
                if cur_sum > max_sum:
                    max_sum = cur_sum
                    max_level = cur_level
            return max_level
        
        return bfs()