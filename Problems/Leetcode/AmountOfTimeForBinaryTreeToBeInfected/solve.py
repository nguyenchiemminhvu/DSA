from typing import Optional
from collections import defaultdict, deque

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def amountOfTime(self, root: Optional[TreeNode], start: int) -> int:
        graph = defaultdict(list)
        def build_graph(root: Optional[TreeNode]):
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

        q = deque([start])
        visited = set([start])
        time = -1
        while q:
            time += 1
            for _ in range(len(q)):
                cur = q.popleft()
                for adj in graph[cur]:
                    if adj not in visited:
                        visited.add(adj)
                        q.append(adj)
        
        return time