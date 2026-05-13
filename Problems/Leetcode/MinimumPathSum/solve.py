from typing import List

class Solution:
    def minPathSum(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        INF = [0x7FFFFFFF]

        # mem = {}
        # def F(r: int, c: int) -> int:
        #     if r < 0 or c < 0:
        #         return INF[0]
        #     if r == 0 and c == 0:
        #         return grid[0][0]
        #     if (r, c) in mem:
        #         return mem[(r, c)]
        #     min_top = F(r - 1, c)
        #     min_left = F(r, c - 1)
        #     min_cur = INF[0]
        #     if min_top != INF[0]:
        #         min_cur = min(min_cur, grid[r][c] + min_top)
        #     if min_left != INF[0]:
        #         min_cur = min(min_cur, grid[r][c] + min_left)
        #     mem[(r, c)] = min_cur
        #     return min_cur
        # return F(m-1, n-1)

        dp = [[INF[0] for _ in range(n)] for _ in range(m)]
        dp[0][0] = grid[0][0]
        for i in range(1, m):
            dp[i][0] = dp[i - 1][0] + grid[i][0]
        for i in range(1, n):
            dp[0][i] = dp[0][i - 1] + grid[0][i]
        for i in range(1, m):
            for j in range(1, n):
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1])
        return dp[m - 1][n - 1]