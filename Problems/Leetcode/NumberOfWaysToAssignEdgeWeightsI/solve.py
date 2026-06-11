from collections import defaultdict, deque
from typing import List

class Solution:
    def assignEdgeWeights(self, edges: List[List[int]]) -> int:
        adj = defaultdict(list)
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
        
        def bfs(node_val: int) -> int:
            q = deque([node_val])
            visited = set()
            visited.add(node_val)
            depth = -1
            while q:
                z = len(q)
                depth += 1
                for _ in range(z):
                    cur = q.popleft()
                    for next_node in adj[cur]:
                        if next_node not in visited:
                            visited.add(next_node)
                            q.append(next_node)
            return depth
        
        depth = bfs(1)

        mod = 10**9 + 7
        mem = {}
        def F(i: int, odd: bool) -> int:
            nonlocal depth, mod
            if i == depth:
                return int(odd)
            
            if (i, odd) in mem:
                return mem[(i, odd)]
            res = 0
            res += F(i + 1, not odd)
            res += F(i + 1, odd)
            res %= mod
            mem[(i, odd)] = res
            return res

        return F(0, False)