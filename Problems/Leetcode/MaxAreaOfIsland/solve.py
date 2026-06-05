from typing import List

class Solution:
    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        def dfs(r, c):
            if r < 0 or r >= m or c < 0 or c >= n:
                return 0
            if grid[r][c] == 0:
                return 0
            
            grid[r][c] = 0
            s = 1
            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                s += dfs(nr, nc)
            return s
        
        res = 0
        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1:
                    res = max(res, dfs(r, c))
        return res