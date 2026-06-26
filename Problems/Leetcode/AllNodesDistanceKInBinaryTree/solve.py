from collections import deque

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def distanceK(self, root: TreeNode, target: TreeNode, k: int) -> List[int]:
        graph = {}
        def build_graph(root, parent):
            if not root:
                return
            if root.val not in graph:
                graph[root.val] = []
            if parent:
                graph[root.val].append(parent.val)
            build_graph(root.left, root)
            build_graph(root.right, root)
            if root.left:
                graph[root.val].append(root.left.val)
            if root.right:
                graph[root.val].append(root.right.val)
        build_graph(root, None)

        q = deque([target.val])
        res = []
        visited = set([target.val])
        steps = -1
        while q:
            steps += 1
            if steps > k:
                break
            
            z = len(q)
            row = []
            for _ in range(z):
                cur = q.popleft()
                row.append(cur)
                for adj in graph[cur]:
                    if adj not in visited:
                        q.append(adj)
                        visited.add(adj)
            
            res = row
        
        if steps < k:
            return []
        
        return res