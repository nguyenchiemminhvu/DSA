from typing import List
from collections import defaultdict
import heapq

class Solution:
    def minTimeMaxPower(self, n: int, edges: List[List[int]], power: int, cost: List[int], source: int, target: int) -> List[int]:
        if source == target:
            return [0, power]
        
        graph = defaultdict(list)
        for u, v, t in edges:
            graph[u].append((t, v))
        
        INF = float('inf')
        used = [[INF] * (power + 1) for _ in range(n)]
        used[source][0] = 0

        pq = [(0, 0, source)] # cur time, cur used power, cur node
        while pq:
            t, p, node = heapq.heappop(pq)

            if t > used[node][p]:
                continue

            if node == target:
                return [t, power - p]
            
            if p + cost[node] > power:
                continue
            
            for next_t, next_node in graph[node]:
                if t + next_t < used[next_node][p + cost[node]]:
                    used[next_node][p + cost[node]] = t + next_t
                    heapq.heappush(pq, (t + next_t, p + cost[node], next_node))
            
        return [-1, -1]