from collections import defaultdict, deque
from typing import List

class Solution:
    def gardenNoAdj(self, n: int, paths: List[List[int]]) -> List[int]:
        graph = defaultdict(list)
        for u, v in paths:
            graph[u - 1].append(v - 1)
            graph[v - 1].append(u - 1)
        
        colors = [-1] * n
        visited = set()
        for i in range(n):
            if i not in visited:
                visited.add(i)
                q = deque([i])
                while q:
                    cur = q.popleft()
                    used_colors = set()
                    for adj in graph[cur]:
                        if colors[adj] != -1:
                            used_colors.add(colors[adj])
                    for color in range(1, 5):
                        if color not in used_colors:
                            colors[cur] = color
                            break
                    
                    for adj in graph[cur]:
                        if adj not in visited:
                            visited.add(adj)
                            q.append(adj)
        
        return colors