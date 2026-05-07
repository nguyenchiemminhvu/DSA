from typing import List

class Solution:
    def minReorder(self, n: int, edges: List[List[int]]) -> int:
        graph = {
            i: [] for i in range(n)
        }

        for u, v in edges:
            graph[u].append((1, v))
            graph[v].append((0, u))
        
        res = 0
        visited = [False] * n
        visited[0] = True
        def dfs(cur: int):
            nonlocal res
            adj = graph[cur]
            for cost, p in adj:
                if not visited[p]:
                    visited[p] = True
                    res += cost
                    dfs(p)
        
        dfs(0)
        return res