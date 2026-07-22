from collections import defaultdict
import heapq
from typing import List

class Solution:
    def minTime(self, n: int, edges: List[List[int]]) -> int:
        graph = defaultdict(list)
        for u, v, s, e in edges:
            graph[u].append((v, s, e))
        
        INF = float('inf')
        cost = [INF] * n
        cost[0] = 0

        pq = [(0, 0)] # cur_time, cur_node
        while pq:
            cur_time, cur_node = heapq.heappop(pq)
            if cur_time > cost[cur_node]:
                continue
            
            for adj, s, e in graph[cur_node]:
                if cur_time > e:
                    continue
                
                next_time = s + 1
                if cur_time > s:
                    next_time = cur_time + 1
                
                if next_time < cost[adj]:
                    cost[adj] = next_time
                    heapq.heappush(pq, (next_time, adj))
        
        if cost[n - 1] == INF:
            return -1
        return cost[n - 1]