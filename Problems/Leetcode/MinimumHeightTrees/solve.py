from collections import defaultdict, deque
from typing import List

class Solution:
    def findMinHeightTrees(self, n: int, edges: List[List[int]]) -> List[int]:
        if n <= 2:
            return [i for i in range(n)]
        
        graph = defaultdict(set)
        for u, v in edges:
            graph[u].add(v)
            graph[v].add(u)
        
        q = deque([i for i in range(n) if len(graph[i]) == 1])
        
        node_count = n
        while node_count > 2:
            z = len(q)
            for _ in range(z):
                cur = q.popleft()
                node_count -= 1
                
                adj = graph[cur].pop()
                graph[adj].remove(cur)

                if len(graph[adj]) == 1:
                    q.append(adj)
        
        return list(q)