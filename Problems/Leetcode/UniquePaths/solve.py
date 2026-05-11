class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        # mem = {}
        # def F(r: int, c: int) -> int:
        #     if r < 0 or c < 0:
        #         return 0
        #     if r == 0 or c == 0:
        #         return 1
        #     if (r, c) in mem:
        #         return mem[(r, c)]
        #     cur = F(r - 1, c) + F(r, c - 1)
        #     mem[(r, c)] = cur
        #     return cur
        # return F(m - 1, n - 1)

        dp = [[0 for _ in range(n)] for _ in range(m)]
        for i in range(m):
            dp[i][0] = 1
        for i in range(n):
            dp[0][i] = 1
        for i in range(1, m):
            for j in range(1, n):
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1]
        return dp[m - 1][n - 1]