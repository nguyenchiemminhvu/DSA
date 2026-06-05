from collections import defaultdict, deque
from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def replaceValueInTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return None
        
        info = defaultdict(int) # info[depth] -> sum

        def bfs():
            q = deque([root])
            depth = -1
            while q:
                z = len(q)
                sum_row = 0
                depth += 1
                for _ in range(z):
                    cur = q.popleft()
                    sum_row += cur.val
                    if cur.left:
                        q.append(cur.left)
                    if cur.right:
                        q.append(cur.right)
                info[depth] = sum_row
        
        def dfs(root, depth):
            if not root:
                return
            
            if depth + 1 in info:
                sum_next_depth = info[depth + 1]
                sum_this_parent = 0
                if root.left:
                    sum_this_parent += root.left.val
                if root.right:
                    sum_this_parent += root.right.val
                
                if root.left:
                    root.left.val = sum_next_depth - sum_this_parent
                if root.right:
                    root.right.val = sum_next_depth - sum_this_parent

            dfs(root.left, depth + 1)
            dfs(root.right, depth + 1)
        
        bfs()
        dfs(root, 0)
        root.val = 0
        return root