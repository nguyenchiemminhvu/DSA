from collections import defaultdict, deque
from typing import List

class Solution:
    def baseUnitConversions(self, conv: List[List[int]]) -> List[int]:
        mod = 10**9 + 7
        graph = defaultdict(list)
        n = 0

        for u, v, f in conv:
            n = max([n, u + 1, v + 1])
            graph[u].append((f, v))
        
        f_arr = [1] * n
        visited = [False] * n
        
        for i in range(n):
            if not visited[i]:
                q = deque([(1, i)])  # (current_factor, node)
                visited[i] = True
                
                while q:
                    cur_f, cur_u = q.popleft()
                    f_arr[cur_u] = cur_f % mod
                    
                    for next_f, next_u in graph[cur_u]:
                        if not visited[next_u]:
                            visited[next_u] = True
                            q.append(((cur_f * next_f) % mod, next_u))
        
        return f_arr
