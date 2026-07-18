from collections import defaultdict, deque
from typing import List

class Solution:
    def possibleBipartition(self, n: int, dislikes: List[List[int]]) -> bool:
        graph = defaultdict(list)
        for u, v in dislikes:
            graph[u - 1].append(v - 1)
            graph[v - 1].append(u - 1)
        
        colors = [-1] * n
        for i in range(n):
            if colors[i] == -1: # not yet give color
                q = deque([(0, i)])
                while q:
                    color, node = q.popleft()
                    colors[node] = color
                    for adj in graph[node]:
                        if colors[adj] == -1:
                            q.append(((color + 1) % 2, adj))
                        else:
                            if colors[adj] == color:
                                return False
        return True