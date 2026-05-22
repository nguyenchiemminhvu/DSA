from typing import List

class Solution:
    def calculateMinimumHP(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        INF = float('inf')

        mem = {}
        def F(r: int, c: int) -> int:
            if r >= m or c >= n:
                return INF
            if r == m - 1 and c == n - 1:
                return max(1, 1 - grid[r][c])
            
            if (r, c) in mem:
                return mem[(r, c)]
            
            need = min(F(r + 1, c), F(r, c + 1))
            res = max(1, -grid[r][c] + need)

            mem[(r, c)] = res
            return res
        
        return F(0, 0)