from typing import List

class Solution:
    def uniquePathsIII(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        start_r, start_c = -1, -1
        total_empty = 0
        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1:
                    start_r, start_c = r, c
                elif grid[r][c] == 0:
                    total_empty += 1

        visited = [[False] * n for _ in range(m)]
        visited[start_r][start_c] = True

        def dfs(r, c, cover):
            if grid[r][c] == 2:
                return 1 if cover == total_empty else 0
            
            res = 0
            for nr, nc in [(r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)]:
                if nr >= 0 and nr < m and nc >= 0 and nc < n:
                    if not visited[nr][nc] and grid[nr][nc] != -1:
                        visited[nr][nc] = True
                        next_cover = cover + 1 if grid[nr][nc] == 0 else cover
                        res += dfs(nr, nc, next_cover)
                        visited[nr][nc] = False
            return res
        
        count = dfs(start_r, start_c, 0)
        return count