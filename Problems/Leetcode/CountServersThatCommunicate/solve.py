from typing import List

class Solution:
    def countServers(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        res = 0
        rows = [0] * m
        cols = [0] * n
        total = 0
        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1:
                    rows[r] += 1
                    cols[c] += 1
                    total += 1
        
        isolated = 0
        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1 and rows[r] == 1 and cols[c] == 1:
                    isolated += 1
        
        return total - isolated