from collections import defaultdict
from typing import List

class Solution:
    def getAncestors(self, n: int, edges: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        in_degree = [0] * n
        for u, v in edges:
            graph[v].append(u) # reversed
            in_degree[u] += 1
        
        parents = [[] for _ in range(n)]

        from functools import lru_cache
        @lru_cache(None)
        def dfs(cur: int) -> List[int]:
            arrs = set()
            for adj in graph[cur]:
                arr = dfs(adj)
                arrs.update(arr)
            parents[cur] = sorted(list(arrs))
            arrs.add(cur)
            return list(arrs)
        
        for i in range(n):
            if in_degree[i] == 0:
                dfs(i)
        
        return parents