from typing import List

class Solution:
    def findColumnWidth(self, grid: List[List[int]]) -> List[int]:
        m = len(grid)
        n = len(grid[0])
        res = [1] * n
        for c in range(n):
            for row in grid:
                res[c] = max(res[c], len(str(row[c])))
        return res