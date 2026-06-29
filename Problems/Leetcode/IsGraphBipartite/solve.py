from collections import deque
from typing import List

class Solution:
    def isBipartite(self, graph: List[List[int]]) -> bool:
        n = len(graph)
        colors = [-1] * n
        def bfs(start: int) -> bool:
            q = deque([(start, 0)])
            colors[start] = 0
            while q:
                node, color = q.popleft()
                next_color = (color + 1) % 2

                for adj in graph[node]:
                    if colors[adj] == -1:
                        colors[adj] = next_color
                        q.append((adj, next_color))
                    else:
                        if next_color != colors[adj]:
                            return False
            return True
        
        for i in range(n):
            if colors[i] == -1:
                if not bfs(i):
                    return False
        return True