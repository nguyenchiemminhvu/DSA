from typing import List

class Solution:
    def allPathsSourceTarget(self, graph: List[List[int]]) -> List[List[int]]:
        n = len(graph)
        res = []
        path = []
        visited = [False] * n
        def dfs(cur: int) -> None:
            if cur == n - 1:
                res.append([0] + path[:])
                return
            
            for adj in graph[cur]:
                if not visited[adj]:
                    visited[adj] = True
                    path.append(adj)
                    dfs(adj)
                    path.pop()
                    visited[adj] = False
        
        visited[0] = True
        dfs(0)
        return res