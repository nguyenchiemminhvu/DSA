from typing import List

class Solution:
    def maxProductPath(self, grid: List[List[int]]) -> int:
        mod = 10**9+7
        m = len(grid)
        n = len(grid[0])
        max_prod = [[0] * n for _ in range(m)]
        min_prod = [[0] * n for _ in range(m)]
        max_prod[0][0] = min_prod[0][0] = grid[0][0]

        for r in range(1, m):
            max_prod[r][0] = max_prod[r-1][0] * grid[r][0]
            min_prod[r][0] = max_prod[r][0]
        for c in range(1, n):
            max_prod[0][c] = max_prod[0][c-1] * grid[0][c]
            min_prod[0][c] = max_prod[0][c]
        
        for i in range(1, m):
            for j in range(1, n):
                val = grid[i][j]
                candidates = [
                    (max_prod[i-1][j] * val),
                    (max_prod[i][j-1] * val),
                    (min_prod[i-1][j] * val),
                    (min_prod[i][j-1] * val),
                ]
                max_prod[i][j] = max(candidates)
                min_prod[i][j] = min(candidates)
        res = max_prod[m-1][n-1]
        return res % mod if res >= 0 else -1