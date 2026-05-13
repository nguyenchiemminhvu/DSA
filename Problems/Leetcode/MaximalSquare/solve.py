from typing import List

class Solution:
    def maximalSquare(self, grid: List[List[str]]) -> int:
        m, n = len(grid), len(grid[0])

        # mem = {}
        # def F(r: int, c: int) -> int:
        #     if r >= m or c >= n or grid[r][c] == '0':
        #         return 0
        #     if (r, c) in mem:
        #         return mem[(r, c)]
        #     down = F(r + 1, c)
        #     right = F(r, c + 1)
        #     down_right = F(r + 1, c + 1)
        #     res = 1 + min(down, right, down_right)
        #     mem[(r, c)] = res
        #     return res
        
        # max_s = 0
        # for i in range(m):
        #     for j in range(n):
        #         max_s = max(max_s, F(i, j))
        # return max_s ** 2

        max_s = 0
        dp = [[0 for _ in range(n + 1)] for _ in range(m + 1)]
        for i in range(m - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                if grid[i][j] == '0':
                    dp[i][j] = 0
                else:
                    dp[i][j] = 1 + min(dp[i + 1][j], dp[i][j + 1], dp[i + 1][j + 1])
                max_s = max(max_s, dp[i][j])
        return max_s ** 2