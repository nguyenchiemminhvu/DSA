from typing import List

class Solution:
    def eventualSafeNodes(self, graph: List[List[int]]) -> List[int]:
        state = {i: 0 for i in range(len(graph))}
        def is_safe(node) -> bool:
            if state[node] > 0:
                return state[node] == 2
            
            state[node] = 1
            for adj in graph[node]:
                if state[adj] == 1:
                    return False
                if state[adj] == 0 and not is_safe(adj):
                    return False
            
            state[node] = 2
            return True
        
        res = []
        for i in range(len(graph)):
            if is_safe(i):
                res.append(i)
        return sorted(res)