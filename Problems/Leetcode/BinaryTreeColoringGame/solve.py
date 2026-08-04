from collections import defaultdict, deque
from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def btreeGameWinningMove(self, root: Optional[TreeNode], n: int, x: int) -> bool:
        graph = defaultdict(list)

        def build_graph(root):
            if not root:
                return
            
            if root.left:
                graph[root.val].append(root.left.val)
                graph[root.left.val].append(root.val)
            if root.right:
                graph[root.val].append(root.right.val)
                graph[root.right.val].append(root.val)
            
            build_graph(root.left)
            build_graph(root.right)
        
        build_graph(root)

        def can_win(y):
            q = deque([x])
            visited = set([x])
            while q:
                cur = q.popleft()
                for adj in graph[cur]:
                    if adj != y and adj not in visited:
                        visited.add(adj)
                        q.append(adj)
            return len(visited) < (n - len(visited))

        for adj in graph[x]:
            if can_win(adj):
                return True
        return False