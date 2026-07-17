from collections import defaultdict, deque
from typing import List

class Solution:
    def shortestDistanceAfterQueries(self, n: int, queries: List[List[int]]) -> List[int]:
        graph = defaultdict(list)
        for i in range(1, n):
            graph[i - 1].append(i)
        
        def shortest_path() -> int:
            INF = 0xFFFFFFFF
            dist = [INF] * n
            q = deque([(0, 0)]) # (cost, node)
            while q:
                cur_cost, cur_node = q.popleft()
                if cur_cost > dist[cur_node]:
                    continue
                
                for adj in graph[cur_node]:
                    if cur_cost + 1 < dist[adj]:
                        dist[adj] = cur_cost + 1
                        q.append((cur_cost + 1, adj))
            return dist[n - 1]
        
        res = []
        for u, v in queries:
            graph[u].append(v)
            res.append(shortest_path())
        return res