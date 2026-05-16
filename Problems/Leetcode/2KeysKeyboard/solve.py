class Solution:
    def minSteps(self, n: int) -> int:
        mem = {}
        def F(i: int, l: int) -> int:
            if i > n:
                return float('inf')
            if i == n:
                return 0
            if (i, l) in mem:
                return mem[(i, l)]
            res = float('inf')
            if l == 0:
                # not yet copied, to move on, it must start with copy operation
                res = min(
                    res,
                    2 + F(i + i, i)
                )
            else:
                res = min(
                    res,
                    1 + F(i + l, l),
                    2 + F(i + i, i)
                )
            mem[(i, l)] = res
            return res
        return F(1, 0)

        # dp = [[float('inf')] * (n + 1) for _ in range(n + 1)]
        # for l in range(n + 1):
        #     dp[n][l] = 0
        
        # for i in range(n, 0, -1):
        #     for l in range(n + 1):
        #         if l == 0:
        #             if i + i <= n:
        #                 dp[i][l] = min(dp[i][l], 2 + dp[i + i][i])
        #         else:
        #             if i + l <= n:
        #                 dp[i][l] = min(dp[i][l], 1 + dp[i + l][l])
        #             if i + i <= n:
        #                 dp[i][l] = min(dp[i][l], 2 + dp[i + i][i])
        # return dp[1][0]