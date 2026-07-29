from collections import defaultdict
from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def pseudoPalindromicPaths (self, root: Optional[TreeNode]) -> int:
        f = defaultdict(int)
        res = 0

        def dfs(root, count_odd):
            nonlocal res
            if not root:
                return
            
            f[root.val] += 1
            if f[root.val] & 1:
                count_odd += 1
            else:
                count_odd -= 1

            if not root.left and not root.right:
                if count_odd <= 1:
                    res += 1

            dfs(root.left, count_odd)
            dfs(root.right, count_odd)

            f[root.val] -= 1
            if f[root.val] & 1:
                count_odd += 1
            else:
                count_odd -= 1
        
        dfs(root, 0)

        return res