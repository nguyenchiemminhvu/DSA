from collections import deque
from typing import List

class Solution:
    def findFarmland(self, grid: List[List[int]]) -> List[List[int]]:
        m, n = len(grid), len(grid[0])
        res = []

        def bfs(r, c):
            tl_r, tl_c = m, n
            br_r, br_c = -1, -1
            q = deque([(r, c)])
            grid[r][c] = 0
            while q:
                r, c = q.popleft()
                grid[r][c] = 0
                tl_r = min(tl_r, r)
                tl_c = min(tl_c, c)
                br_r = max(br_r, r)
                br_c = max(br_c, c)
                for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                    if nr >= 0 and nr < m and nc >= 0 and nc < n:
                        if grid[nr][nc] == 1:
                            grid[nr][nc] = 0
                            q.append((nr, nc))
            return [tl_r, tl_c, br_r, br_c]
        
        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1:
                    bound = bfs(r, c)
                    res.append(bound)
        return res