from collections import defaultdict, deque
from typing import List
import heapq

class Solution:
    def minScore(self, n: int, roads: List[List[int]]) -> int:
        adj = defaultdict(list)
        for u, v, d in roads:
            adj[u].append((d, v))
            adj[v].append((d, u))
        
        res = float('inf')
        q = deque([1])
        visited = set()
        visited.add(1)
        while q:
            cur = q.popleft()
            for d, next_node in adj[cur]:
                res = min(res, d)
                if next_node not in visited:
                    visited.add(next_node)
                    q.append(next_node)
        
        return res