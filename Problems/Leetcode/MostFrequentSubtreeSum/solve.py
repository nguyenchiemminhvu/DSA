from collections import defaultdict
from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def findFrequentTreeSum(self, root: Optional[TreeNode]) -> List[int]:
        freq = defaultdict(int)

        def dfs(root):
            if not root:
                return 0
            
            left = dfs(root.left)
            right = dfs(root.right)

            s = left + right + root.val
            freq[s] += 1
            return s
        
        dfs(root)

        res = []
        max_freq = max(freq.values())
        for k, count in freq.items():
            if count == max_freq:
                res.append(k)
        return res