from typing import List
from collections import defaultdict

class Solution:
    def checkIfPrerequisite(self, n: int, pre: List[List[int]], queries: List[List[int]]) -> List[bool]:
        reachable = [[False] * n for _ in range(n)]
        for i in range(n):
            reachable[i][i] = True
        
        graph = defaultdict(list)
        for u, v in pre:
            graph[u].append(v)
        
        from functools import lru_cache
        @lru_cache(None)
        def dfs(cur: int, target: int) -> bool:
            if cur == target:
                return True
            for adj in graph[cur]:
                if dfs(adj, target):
                    return True
            return False
        
        res = []
        for u, v in queries:
            res.append(dfs(u, v))
        return res