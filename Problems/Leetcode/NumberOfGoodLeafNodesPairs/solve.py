from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def countPairs(self, root: Optional[TreeNode], distance: int) -> int:
        self.res = 0

        def dfs(root):
            if not root:
                return []
            
            if not root.left and not root.right:
                return [1]
            
            left = dfs(root.left)
            right = dfs(root.right)

            for l in left:
                for r in right:
                    if l + r <= distance:
                        self.res += 1
            
            new_dist = []
            for d in left + right:
                if d + 1 <= distance:
                    new_dist.append(d + 1)
            
            return new_dist
        
        dfs(root)
        return self.res