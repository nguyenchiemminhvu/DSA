from typing import List

class Solution:
    def checkXMatrix(self, grid: List[List[int]]) -> bool:
        s = set()
        n = len(grid)
        for i in range(n):
            if grid[i][i] == 0:
                return False
            j = n - i - 1
            if grid[i][j] == 0:
                return False
        
        for i in range(n):
            for j in range(n):
                if j != i and j != (n - i - 1):
                    if grid[i][j] != 0:
                        return False

        return True