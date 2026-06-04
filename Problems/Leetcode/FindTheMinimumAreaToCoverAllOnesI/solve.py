from typing import List

class Solution:
    def minimumArea(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        min_row = m
        max_row = -1
        min_col = n
        max_col = -1
        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1:
                    min_row = min(min_row, r)
                    max_row = max(max_row, r)
                    min_col = min(min_col, c)
                    max_col = max(max_col, c)
        
        return (max_row - min_row + 1) * (max_col - min_col + 1)