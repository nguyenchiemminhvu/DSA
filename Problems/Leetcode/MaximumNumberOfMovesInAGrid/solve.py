from typing import List

class Solution:
    def maxMoves(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        mem = {}
        def F(r: int, c: int) -> int:
            if r < 0 or r >= m or c < 0 or c >= n:
                return 0
            if (r, c) in mem:
                return mem[(r, c)]
            res = 0
            for nr, nc in [(r - 1, c + 1), (r, c + 1), (r + 1, c + 1)]:
                if nr >= 0 and nr < m and nc >= 0 and nc < n:
                    if grid[r][c] < grid[nr][nc]:
                        res = max(res, 1 + F(nr, nc))
            mem[(r, c)] = res
            return res
        
        res = 0
        for r in range(m):
            res = max(res, F(r, 0))
        return res