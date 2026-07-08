from collections import defaultdict
from typing import List

class Solution:
    def remainingMethods(self, n: int, k: int, edges: List[List[int]]) -> List[int]:
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
        
        visited = set()
        def dfs(node: int):
            if node in visited:
                return
            
            visited.add(node)
            for adj in graph[node]:
                dfs(adj)
        
        dfs(k)

        valid = True
        for i in range(n):
            if not valid:
                break
            if i not in visited:
                for adj in graph[i]:
                    if adj in visited:
                        valid = False
                        break
        
        if valid:
            return [i for i in range(n) if i not in visited]
        
        return list(range(n))