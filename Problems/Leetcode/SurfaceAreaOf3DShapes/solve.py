from typing import List

class Solution:
    def surfaceArea(self, grid: List[List[int]]) -> int:
        res = sum([sum(row) for row in grid]) * 6
        for row in grid:
            for val in row:
                if val > 0:
                    res -= (val - 1) * 2

        n = len(grid)
        for i in range(n):
            for j in range(n):
                if i > 0:
                    res -= min(grid[i][j], grid[i - 1][j]) * 2
                if j > 0:
                    res -= min(grid[i][j], grid[i][j - 1]) * 2
        return res