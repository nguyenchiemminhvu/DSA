from collections import defaultdict
import heapq

class Solution:
    def networkDelayTime(self, times: List[List[int]], n: int, k: int) -> int:
        adj = defaultdict(list)
        for u, v, t in times:
            adj[u].append((t, v))
        
        dist = [float('inf')] * (n + 1)
        dist[0] = dist[k] = 0
        pq = [(0, k)]
        while pq:
            cur_time, cur_node = heapq.heappop(pq)

            if cur_time > dist[cur_node]:
                continue

            for next_time, next_node in adj[cur_node]:
                if dist[next_node] > cur_time + next_time:
                    dist[next_node] = cur_time + next_time
                    heapq.heappush(pq, (cur_time + next_time, next_node))
        
        res = max(dist)
        return -1 if res == float('inf') else res