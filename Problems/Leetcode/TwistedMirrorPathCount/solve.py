from typing import List

class Solution:
    def uniquePaths(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        MOD = 10**9 + 7

        # mem = {}
        # def F(i: int, j: int, dir: int) -> int:
        #     if i >= m or j >= n:
        #         return 0
        #     if i == m - 1 and j == n - 1:
        #         return 1
        #     if (i, j, dir) in mem:
        #         return mem[(i, j, dir)]
        #     res = 0
        #     if grid[i][j] == 0:
        #         # 2 directions
        #         res += F(i, j + 1, 0) # go right
        #         res += F(i + 1, j, 1) # go down
        #     else:
        #         if dir == 0:
        #             res += F(i + 1, j, 1) # force go down
        #         else:
        #             res += F(i, j + 1, 0) # force go right
        #     mem[(i, j, dir)] = res % MOD
        #     return res % MOD
        # return F(0, 0, 0)

        dp = [[[0] * 2 for _ in range(n)] for _ in range(m)]
        dp[m - 1][n - 1][0] = 1
        dp[m - 1][n - 1][1] = 1
        for i in range(m - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                if i == m - 1 and j == n - 1:
                    continue
                if grid[i][j] == 0:
                    # Can move right or down
                    dp[i][j][0] = (
                        (dp[i][j + 1][0] if j + 1 < n else 0) +
                        (dp[i + 1][j][1] if i + 1 < m else 0)
                    ) % MOD

                    dp[i][j][1] = (
                        (dp[i][j + 1][0] if j + 1 < n else 0) +
                        (dp[i + 1][j][1] if i + 1 < m else 0)
                    ) % MOD
                else:
                    dp[i][j][0] = (
                        dp[i + 1][j][1] if i + 1 < m else 0
                    )
                    dp[i][j][1] = (
                        dp[i][j + 1][0] if j + 1 < n else 0
                    )
        return dp[0][0][0]