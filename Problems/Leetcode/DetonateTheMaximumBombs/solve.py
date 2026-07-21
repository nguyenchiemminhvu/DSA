from collections import defaultdict, deque
import math
from typing import List

class Solution:
    def maximumDetonation(self, bombs: List[List[int]]) -> int:
        n = len(bombs)

        graph = defaultdict(list)
        for i in range(n):
            xi, yi, ri = bombs[i]
            for j in range(n):
                if i == j:
                    continue
                
                xj, yj, rj = bombs[j]
                dist = math.sqrt((xj - xi) ** 2 + (yj - yi) ** 2)
                if dist <= ri:
                    graph[i].append(j)
        
        def bfs(start: int) -> int:
            count = 0
            q = deque([start])
            visited = set([start])
            while q:
                cur = q.popleft()
                count += 1
                for adj in graph[cur]:
                    if adj not in visited:
                        visited.add(adj)
                        q.append(adj)
            return count
        
        res = 0
        for i in range(n):
            res = max(res, bfs(i))
        return res