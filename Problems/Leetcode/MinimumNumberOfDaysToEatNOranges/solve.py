class Solution:
    def minDays(self, n: int) -> int:
        # def F(val: int) -> int:
        #     if val <= 0:
        #         return 0
        #     res = 1 + F(val - 1)
        #     if val % 2 == 0:
        #         res = min(res, 1 + F(val // 2))
        #     if val % 3 == 0:
        #         res = min(res, 1 + F(val // 3))
        #     return res
        # return F(n)

        # dp = [float('inf')] * (n + 1)
        # dp[0] = 0
        # for val in range(1, n + 1):
        #     dp[val] = 1 + dp[val - 1]
        #     if val % 2 == 0:
        #         dp[val] = min(dp[val], 1 + dp[val // 2])
        #     if val % 3 == 0:
        #         dp[val] = min(dp[val], 1 + dp[val // 3])
        # return dp[n]

        from functools import lru_cache
        @lru_cache(None)
        def dfs(val: int) -> int:
            if val <= 1:
                return val
            return 1 + min(
                val % 3 + dfs(val // 3),
                val % 2 + dfs(val // 2)
            )
        
        return dfs(n)