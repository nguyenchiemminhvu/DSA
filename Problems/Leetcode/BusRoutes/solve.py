from collections import deque
from typing import List

class Solution:
    def numBusesToDestination(self, routes: List[List[int]], source: int, target: int) -> int:
        if source == target:
            return 0
        
        n_route = len(routes)
        routes = [set(route) for route in routes]

        q = deque([i for i in range(n_route) if source in routes[i]])
        visited = set()
        steps = 0
        while q:
            steps += 1
            z = len(q)
            for _ in range(z):
                cur_line = q.popleft()
                if target in routes[cur_line]:
                    return steps

                for i in range(n_route):
                    if i not in visited:
                        if len(routes[cur_line] & routes[i]) > 0:
                            visited.add(i)
                            q.append(i)
        
        return -1