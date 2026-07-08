from collections import defaultdict, deque
from typing import List

class Solution:
    def reachableNodes(self, n: int, edges: List[List[int]], restricted: List[int]) -> int:
        restricted = set(restricted)
        if 0 in restricted:
            return 0
        
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        q = deque([0])
        visited = set()
        visited.add(0)
        count = 0
        while q:
            cur = q.popleft()
            count += 1
            for adj in graph[cur]:
                if adj not in restricted and adj not in visited:
                    q.append(adj)
                    visited.add(adj)
        
        return count