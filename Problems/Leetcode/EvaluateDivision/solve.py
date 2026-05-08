from typing import List

class Solution:
    def calcEquation(self, equations: List[List[str]], values: List[float], queries: List[List[str]]) -> List[float]:
        graph = {} # str -> (val, str)
        for i in range(len(values)):
            var1, var2 = equations[i]
            val = values[i]
            graph.setdefault(var1, []).append((val, var2))
            graph.setdefault(var2, []).append((1/val, var1))
        
        def dfs(cur: str, target: str, visited: set[str]):
            if cur == target:
                return 1.0
            
            visited.add(cur)
            for next_cost, next_node in graph[cur]:
                if next_node not in visited:
                    res = dfs(next_node, target, visited)
                    if res != -1.0:
                        return res * next_cost
            return -1.0

        res = []
        for var1, var2 in queries:
            if var1 not in graph or var2 not in graph:
                res.append(-1.0)
            else:
                res.append(dfs(var1, var2, set()))
        return res