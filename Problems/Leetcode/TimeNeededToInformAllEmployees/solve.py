from typing import List

class Solution:
    def numOfMinutes(self, n: int, headID: int, manager: List[int], informTime: List[int]) -> int:
        graph = { i: [] for i in range(n) }
        for i, lead in enumerate(manager):
            if lead != -1:
                graph[lead].append(i)
        
        self.res = 0
        def dfs(cur: int, cost: int):
            self.res = max(self.res, cost)
            for adj in graph[cur]:
                dfs(adj, cost + informTime[cur])
        
        dfs(headID, 0)
        return self.res