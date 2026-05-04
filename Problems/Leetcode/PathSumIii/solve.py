from typing import Optional
from collections import defaultdict

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def pathSum(self, root: Optional[TreeNode], target: int) -> int:
        prefix_sum_count = defaultdict(int)
        prefix_sum_count[0] = 1
        res = [0]

        def dfs(root: Optional[TreeNode], cur_sum: int):
            if not root:
                return
            
            cur_sum += root.val
            res[0] += prefix_sum_count[cur_sum - target]
            prefix_sum_count[cur_sum] += 1
            dfs(root.left, cur_sum)
            dfs(root.right, cur_sum)
            prefix_sum_count[cur_sum] -= 1
        
        dfs(root, 0)
        return res[0]