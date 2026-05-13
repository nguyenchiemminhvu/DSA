from typing import List

class Solution:
    def minFallingPathSum(self, grid: List[List[int]]) -> int:
        n = len(grid)

        # mem = {}
        # def F(r: int, c: int) -> int:
        #     if c < 0 or c >= n:
        #         return float('inf')
        #     if r == n - 1:
        #         return grid[r][c]
        #     if (r, c) in mem:
        #         return mem[(r, c)]
        #     res = grid[r][c] + min(F(r + 1, c - 1), F(r + 1, c), F(r + 1, c + 1))
        #     mem[(r, c)] = res
        #     return res
        
        # res = float('inf')
        # for i in range(n):
        #     res = min(res, F(0, i))
        # return res

        dp = [[float('inf') for _ in range(n + 2)] for _ in range(n)]
        for i in range(n):
            dp[n - 1][i + 1] = grid[n - 1][i]
        
        for r in range(n - 2, -1, -1):
            for c in range(1, n + 1):
                dp[r][c] = grid[r][c - 1] + min(dp[r + 1][c - 1], dp[r + 1][c], dp[r + 1][c + 1])

        res = float('inf')
        for i in range(1, n + 1):
            res = min(res, dp[0][i])
        return res