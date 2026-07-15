from typing import List
import heapq

class Solution:
    def minTimeToReach(self, move_time: List[List[int]]) -> int:
        m, n = len(move_time), len(move_time[0])
        INF = 0xFFFFFFFF

        dp = [[INF] * n for _ in range(m)]
        dp[0][0] = 0
        pq = [(0, (0, 0))]
        while pq:
            cur_time, (r, c) = heapq.heappop(pq)
            if cur_time > dp[r][c]:
                continue

            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                if nr < 0 or nr >= m or nc < 0 or nc >= n:
                    continue
                
                next_cost = move_time[nr][nc] + 1
                if cur_time >= move_time[nr][nc]:
                    next_cost = cur_time + 1
                
                if dp[nr][nc] > next_cost:
                    dp[nr][nc] = next_cost
                    heapq.heappush(pq, (next_cost, (nr, nc)))
        
        return dp[m - 1][n - 1]