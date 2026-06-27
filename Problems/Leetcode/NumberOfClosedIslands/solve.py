from collections import deque
from typing import List

class Solution:
    def closedIsland(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        def bfs(r, c):
            valid = True
            q = deque([(r, c)])
            while q:
                r, c = q.popleft()
                if r == 0 or r == m - 1 or c == 0 or c == n - 1:
                    valid = False
                grid[r][c] = 2
                for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                    if nr >= 0 and nr < m and nc >= 0 and nc < n:
                        if grid[nr][nc] == 0:
                            q.append((nr, nc))
            return valid
        
        res = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 0:
                    check = bfs(i, j)
                    res += check
        return res