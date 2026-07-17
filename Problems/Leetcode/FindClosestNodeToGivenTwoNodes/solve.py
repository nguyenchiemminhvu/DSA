from collections import defaultdict, deque
from typing import List

class Solution:
    def closestMeetingNode(self, edges: List[int], node1: int, node2: int) -> int:
        INF = float('inf')
        n = len(edges)

        graph = defaultdict(list)
        for i in range(len(edges)):
            if edges[i] != -1:
                graph[i].append(edges[i])
        
        def shortest_path(node: int) -> List[int]:
            dist = [INF] * n
            dist[node] = 0
            q = deque([(0, node)])
            while q:
                d, node = q.popleft()
                if d > dist[node]:
                    continue
                
                for adj in graph[node]:
                    if d + 1 < dist[adj]:
                        dist[adj] = d + 1
                        q.append((dist[adj], adj))
            return dist
        
        dist1 = shortest_path(node1)
        dist2 = shortest_path(node2)

        shortest = INF
        res_node = -1
        for i in range(n):
            d1 = dist1[i]
            d2 = dist2[i]
            if d1 != INF and d2 != INF:
                if shortest > max(d1, d2):
                    res_node = i
                    shortest = max(d1, d2)
        
        return res_node