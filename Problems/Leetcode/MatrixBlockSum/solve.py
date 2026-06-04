from typing import List

class Solution:
    def matrixBlockSum(self, grid: List[List[int]], k: int) -> List[List[int]]:
        def cumsum(grid):
            if not grid or not grid[0]:
                return []
            m, n = len(grid), len(grid[0])
            cum_grid = [[0 for _ in range(n)] for _ in range(m)]
            for r in range(m):
                for c in range(n):
                    val = grid[r][c]
                    if r > 0:
                        val += cum_grid[r-1][c]
                    if c > 0:
                        val += cum_grid[r][c-1]
                    if r > 0 and c > 0:
                        val -= cum_grid[r-1][c-1] # Subtract overlap
                    cum_grid[r][c] = val
            return cum_grid
        
        m, n = len(grid), len(grid[0])
        cum_grid = cumsum(grid)
        res = [[0] * n for _ in range(m)]
        for r in range(m):
            for c in range(n):
                r1 = max(0, r - k)
                c1 = max(0, c - k)
                r2 = min(m - 1, r + k)
                c2 = min(n - 1, c + k)
                total_sum = cum_grid[r2][c2]
                if r1 > 0:
                    total_sum -= cum_grid[r1 - 1][c2]
                if c1 > 0:
                    total_sum -= cum_grid[r2][c1 - 1]
                if r1 > 0 and c1 > 0:
                    total_sum += cum_grid[r1 - 1][c1 - 1]
                res[r][c] = total_sum
        return res