from typing import List
from collections import defaultdict
import heapq

class Solution:
    def shortestPath(self, n: int, edges: List[List[int]], labels: str, k: int) -> int:
        inf = float('inf')

        graph = defaultdict(list)
        for u, v, w in edges:
            graph[u].append((w, v))

        dist = [[inf] * (k + 1) for _ in range(n)]
        dist[0][1] = 0

        pq = [(0, 0, 1)] # cur_dist, cur_node, cur_cons
        while pq:
            cur_dist, cur_node, cur_cons = heapq.heappop(pq)
            if cur_dist > dist[cur_node][cur_cons]:
                continue

            for adj_dist, adj_node in graph[cur_node]:
                next_cons = cur_cons + 1 if (labels[cur_node] == labels[adj_node]) else 1
                if next_cons > k:
                    continue
                next_dist = cur_dist + adj_dist
                if next_dist < dist[adj_node][next_cons]:
                    dist[adj_node][next_cons] = next_dist
                    heapq.heappush(pq, (next_dist, adj_node, next_cons))
        
        res = min(dist[n - 1])
        return -1 if res == inf else res