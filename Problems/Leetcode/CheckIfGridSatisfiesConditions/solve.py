from typing import List

class Solution:
    def satisfiesConditions(self, grid: List[List[int]]) -> bool:
        m = len(grid)
        n = len(grid[0])
        first_row = grid[0]
        for i in range(1, n):
            if first_row[i] == first_row[i - 1]:
                return False
        
        for row in grid:
            if row != first_row:
                return False
        
        return True