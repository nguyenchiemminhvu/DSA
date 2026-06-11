from collections import defaultdict, deque
from typing import List

class Solution:
    def shortestAlternatingPaths(self, n: int, red_edges: List[List[int]], blue_edges: List[List[int]]) -> List[int]:
        res = [float('inf')] * n
        res[0] = 0

        mp_red = defaultdict(list)
        mp_blue = defaultdict(list)
        for u, v in red_edges:
            mp_red[u].append(v)
        
        for u, v in blue_edges:
            mp_blue[u].append(v)
        
        def bfs(start_with_red: bool):
            q = deque([(start_with_red, 0)])
            visited = set()
            visited.add((start_with_red, 0))
            steps = -1
            while q:
                steps += 1
                z = len(q)
                for _ in range(z):
                    is_red, node = q.popleft()
                    if steps < res[node]:
                        res[node] = steps
                    
                    adj = mp_red[node]
                    if is_red:
                        adj = mp_blue[node]
                    
                    for next_node in adj:
                        if (not is_red, next_node) not in visited:
                            visited.add((not is_red, next_node))
                            q.append((not is_red, next_node))
        
        bfs(True)
        bfs(False)
        for i in range(1, n):
            if res[i] == float('inf'):
                res[i] = -1
        return res