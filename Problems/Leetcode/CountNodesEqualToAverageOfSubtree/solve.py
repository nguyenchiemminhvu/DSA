from typing import Optional, Tuple

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def averageOfSubtree(self, root: TreeNode) -> int:
        count = 0
        def dfs(root: Optional[TreeNode]) -> Tuple[int]:
            nonlocal count
            if not root:
                return (0, 0)
            
            left = dfs(root.left)
            right = dfs(root.right)

            s = left[0] + right[0] + root.val
            c = left[1] + right[1] + 1
            if s // c == root.val:
                count += 1
            
            return (s, c)
        
        dfs(root)
        return count