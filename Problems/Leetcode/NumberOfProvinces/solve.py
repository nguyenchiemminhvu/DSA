from typing import List

class Solution:
    def findCircleNum(self, graph: List[List[int]]) -> int:
        n = len(graph)
        count = 0
        visited = set()

        def dfs(cur: int):
            for u in range(n):
                if u not in visited and graph[cur][u]:
                    visited.add(u)
                    dfs(u)

        for i in range(n):
            if i not in visited:
                visited.add(i)
                dfs(i)
                count += 1
        return count