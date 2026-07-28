from collections import defaultdict, deque
from typing import List

class Solution:
    def restoreArray(self, pairs: List[List[int]]) -> List[int]:
        graph = defaultdict(list)
        for u, v in pairs:
            graph[u].append(v)
            graph[v].append(u)
        
        first_node = None
        for u in graph:
            if len(graph[u]) == 1:
                first_node = u
                break
        
        if not first_node:
            return []
        
        res = []
        q = deque([first_node])
        visited = set([first_node])
        while q:
            cur = q.popleft()
            res.append(cur)
            for adj in graph[cur]:
                if adj not in visited:
                    visited.add(adj)
                    q.append(adj)
        return res