from collections import defaultdict
from typing import List
import heapq

class Solution:
    def minimumWeight(self, n: int, edges: List[List[int]], src1: int, src2: int, dest: int) -> int:
        INF = float('inf')
        adj = defaultdict(list)
        adj_rev = defaultdict(list)
        for u, v, d in edges:
            adj[u].append((d, v))
            adj_rev[v].append((d, u))
        
        def shortest_path(source, rev: bool) -> List[int]:
            adj_ref = adj
            if rev:
                adj_ref = adj_rev
            
            dist = [INF] * n
            dist[source] = 0
            pq = [(0, source)]
            while pq:
                cur_dist, cur_node = heapq.heappop(pq)
                if cur_dist > dist[cur_node]:
                    continue
                for next_dist, next_node in adj_ref[cur_node]:
                    if dist[next_node] > cur_dist + next_dist:
                        heapq.heappush(pq, (cur_dist + next_dist, next_node))
                        dist[next_node] = cur_dist + next_dist
            return dist
        
        dist1 = shortest_path(src1, False)
        dist2 = shortest_path(src2, False)
        dist_dest = shortest_path(dest, True)

        res = INF
        for common in range(n):
            if dist1[common] != INF and dist2[common] != INF and dist_dest[common] != INF:
                res = min(res, dist1[common] + dist2[common] + dist_dest[common])
        
        return -1 if res == INF else res