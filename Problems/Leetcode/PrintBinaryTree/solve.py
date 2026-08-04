from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def printTree(self, root: Optional[TreeNode]) -> List[List[str]]:
        def height(root):
            if not root:
                return -1
            return 1 + max(height(root.left), height(root.right))
        
        h = height(root)
        row = h + 1
        col = 2 ** (h + 1) - 1
        grid = [[''] * col for _ in range(row)]

        mid_col = (col - 1) // 2

        # fill grid

        def dfs(root, r, c):
            if not root:
                return
            
            grid[r][c] = str(root.val)
            shift = 2 ** (h - r - 1)

            dfs(root.left, r + 1, c - shift)
            dfs(root.right, r + 1, c + shift)
        
        dfs(root, 0, mid_col)

        return grid