from typing import List
from collections import defaultdict, deque

class Solution:
    def minMaxWeight(self, n: int, edges: List[List[int]], threshold: int) -> int:        
        graph = defaultdict(list)
        for u, v, w in edges:
            graph[v].append((u, w))  # reversed
        
        def can(bound):
            visited = [False] * n
            q = deque([0])
            visited[0] = True
            count = 1
            
            while q:
                node = q.popleft()
                for nei, w in graph[node]:
                    if w <= bound and not visited[nei]:
                        visited[nei] = True
                        count += 1
                        if count == n:
                            return True
                        q.append(nei)
            
            return count == n
        
        low, high = 1, max(w for _, _, w in edges)
        res = -1
        
        while low <= high:
            mid = (low + high) // 2
            if can(mid):
                res = mid
                high = mid - 1
            else:
                low = mid + 1
        
        return res