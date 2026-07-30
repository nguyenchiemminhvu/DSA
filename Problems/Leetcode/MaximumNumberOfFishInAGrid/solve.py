from typing import List

class Solution:
    def findMaxFish(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        def dfs(r, c):
            if r < 0 or r >= m or c < 0 or c >= n:
                return 0
            if grid[r][c] == 0:
                return 0
            
            fish = grid[r][c]
            grid[r][c] = 0
            fish += dfs(r + 1, c)
            fish += dfs(r - 1, c)
            fish += dfs(r, c + 1)
            fish += dfs(r, c - 1)
            return fish
        
        res = 0
        for r in range(m):
            for c in range(n):
                if grid[r][c] > 0:
                    res = max(res, dfs(r, c))
        return res