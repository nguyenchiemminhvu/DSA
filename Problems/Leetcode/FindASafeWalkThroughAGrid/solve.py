from collections import deque
from typing import List

class Solution:
    def findSafeWalk(self, grid: List[List[int]], health: int) -> bool:
        INF = 0xFFFFFFFF
        m, n = len(grid), len(grid[0])

        dp = [[INF] * n for _ in range(m)]
        dp[0][0] = grid[0][0]
        q = deque([(0, 0)])
        while q:
            r, c = q.popleft()
            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                if nr >= 0 and nr < m and nc >= 0 and nc < n:
                    cost = grid[nr][nc]
                    if dp[r][c] + cost < dp[nr][nc]:
                        dp[nr][nc] = dp[r][c] + cost
                        
                        if cost == 0:
                            q.appendleft((nr, nc))
                        else:
                            q.append((nr, nc))
        
        final_cost = dp[m - 1][n - 1]
        return final_cost < health