from typing import List

class Solution:
    def countSquares(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        # ========================================
        # mem = {}
        # # F(r, c) -> (max size square from 0-0 to r-c)
        # def F(r: int, c: int) -> int:
        #     if r >= m or c >= n or grid[r][c] == 0:
        #         return 0
        #     if (r, c) in mem:
        #         return mem[(r, c)]
        #     down = F(r + 1, c)
        #     right = F(r, c + 1)
        #     down_right = F(r + 1, c + 1)
        #     res = 1 + min(down, right, down_right)
        #     mem[(r, c)] = res
        #     return res
        
        # res = 0
        # for r in range(m):
        #     for c in range(n):
        #         res += F(r, c)
        # return res

        # ==========================================
        res = 0
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        for r in range(m - 1, -1, -1):
            for c in range(n - 1, -1, -1):
                if grid[r][c] == 0:
                    continue
                dp[r][c] = 1 + min(dp[r + 1][c], dp[r][c + 1], dp[r + 1][c + 1])
                res += dp[r][c]
        return res