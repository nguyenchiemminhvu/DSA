from typing import List
import heapq

class Solution:
    def minimumEffortPath(self, heights: List[List[int]]) -> int:
        INF = 0xFFFFFFFF
        m, n = len(heights), len(heights[0])
        efforts = [[INF] * n for _ in range(m)]
        efforts[0][0] = 0

        pq = [(0, (0, 0))]
        while pq:
            cur_effort, (r, c) = heapq.heappop(pq)

            if cur_effort > efforts[r][c]:
                continue

            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                if nr < 0 or nr >= m or nc < 0 or nc >= n:
                    continue
                
                next_effort = abs(heights[r][c] - heights[nr][nc])
                if efforts[nr][nc] > max(cur_effort, next_effort):
                    efforts[nr][nc] = max(cur_effort, next_effort)
                    heapq.heappush(pq, (efforts[nr][nc], (nr, nc)))
        
        return efforts[m - 1][n - 1]