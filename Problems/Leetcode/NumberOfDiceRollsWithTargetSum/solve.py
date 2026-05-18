class Solution:
    def numRollsToTarget(self, n: int, k: int, target: int) -> int:
        mod = 10**9 + 7
        
        # from functools import lru_cache
        # @lru_cache(maxsize=128)
        # def F(i: int, remain: int) -> int:
        #     if i < 0:
        #         return 0
        #     if i == 0:
        #         return int(remain == 0)
        #     if remain < 0:
        #         return 0
        #     if remain == 0:
        #         return int(i == 0)
        #     ways = 0
        #     for val in range(1, k + 1):
        #         ways += F(i - 1, remain - val)
        #     return ways
        # return F(n, target)

        dp = [[0] * (target + 1) for _ in range(n + 1)]
        dp[0][0] = 1
        for i in range(n + 1):
            for remain in range(target + 1):
                if i - 1 >= 0:
                    for val in range(1, k + 1):
                        if remain - val >= 0:
                            dp[i][remain] += dp[i - 1][remain - val]
                            dp[i][remain] %= mod
        return dp[n][target]