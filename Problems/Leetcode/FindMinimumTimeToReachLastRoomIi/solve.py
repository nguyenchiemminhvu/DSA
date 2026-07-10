from typing import List
import heapq

class Solution:
    def minTimeToReach(self, move_time: List[List[int]]) -> int:
        INF = 0xFFFFFFFF
        m, n = len(move_time), len(move_time[0])
        dist = [[INF] * n for _ in range(m)]
        dist[0][0] = 0
        pq = [(0, (0, 0))]
        while pq:
            t, (r, c) = heapq.heappop(pq)
            if t > dist[r][c]:
                continue
            
            cost_next_step = ((r + c) % 2) + 1
            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                if 0 <= nr < m and 0 <= nc < n:
                    next_t = move_time[nr][nc] + cost_next_step
                    if t >= move_time[nr][nc]:
                        next_t = t + cost_next_step
                    
                    if dist[nr][nc] > next_t:
                        dist[nr][nc] = next_t
                        heapq.heappush(pq, (next_t, (nr, nc)))
        
        return -1 if dist[m - 1][n - 1] == INF else dist[m - 1][n - 1]