from typing import List

class Solution:
    def projectionArea(self, grid: List[List[int]]) -> int:
        res = 0
        
        n = len(grid)
        for row in grid:
            res += sum(1 for val in row if val > 0)
        
        for row in grid:
            res += max(row)
        
        for i in range(n):
            max_col = 0
            for row in grid:
                max_col = max(max_col, row[i])
            res += max_col
        
        return res
