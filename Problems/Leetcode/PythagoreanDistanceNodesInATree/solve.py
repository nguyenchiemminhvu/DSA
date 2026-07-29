from collections import defaultdict, deque
from typing import List

class Solution:
    def specialNodes(self, n: int, edges: List[List[int]], x: int, y: int, z: int) -> int:
        INF = float('inf')

        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        def shortest_dist(start: int) -> List[int]:
            dist = [INF] * n
            q = deque([start])
            visited = set([start])
            cur_dist = -1
            while q:
                cur_dist += 1
                for _ in range(len(q)):
                    cur = q.popleft()
                    dist[cur] = cur_dist
                    for adj in graph[cur]:
                        if adj not in visited:
                            visited.add(adj)
                            q.append(adj)
            return dist
        
        dist_x = shortest_dist(x)
        dist_y = shortest_dist(y)
        dist_z = shortest_dist(z)

        count = 0
        for i in range(n):
            arr = sorted([dist_x[i], dist_y[i], dist_z[i]])
            a, b, c = arr
            if a ** 2 + b ** 2 == c ** 2:
                count += 1
        
        return count