from typing import Optional, Set
from collections import deque

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def subtreeWithAllDeepest(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def bfs() -> Set[TreeNode]:
            deepest_nodes = set()
            level = 0
            q = deque([root])
            while q:
                size = len(q)
                row = []
                level += 1
                for _ in range(size):
                    cur_node = q.pop()
                    row.append(cur_node)
                    if cur_node.left:
                        q.appendleft(cur_node.left)
                    if cur_node.right:
                        q.appendleft(cur_node.right)
                deepest_nodes = set([(level, node) for node in row])
            return deepest_nodes
        
        deepest_nodes = bfs()
        
        def dfs(root: Optional[TreeNode], level:int = 1):
            nonlocal deepest_nodes
            if not root:
                return
            dfs(root.left, level + 1)
            dfs(root.right, level + 1)
            if root.left and (level + 1, root.left) in deepest_nodes:
                deepest_nodes.add((level, root))
            if root.right and (level + 1, root.right) in deepest_nodes:
                deepest_nodes.add((level, root))
        
        dfs(root, 1)

        # find largest level that has one single node
        f = {}
        for level, node in deepest_nodes:
            f[level] = f.get(level, 0) + 1
        deep_single_level = sorted(f.keys(), key=lambda x: (f[x], -x))[0]
        for level, node in deepest_nodes:
            if level == deep_single_level:
                return node
        return None