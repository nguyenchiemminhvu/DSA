from typing import List

class Solution:
    def maxProfit(self, prices: List[int], fee: int) -> int:
        n = len(prices)

        # mem = {}
        # def F(i: int, hold: bool) -> int:
        #     if i >= n:
        #         return 0
        #     if (i, hold) in mem:
        #         return mem[(i, hold)]
        #     ret = 0
        #     ret = max(ret, F(i + 1, hold))
        #     if hold:
        #         ret = max(ret, prices[i] + F(i + 1, False))
        #     else:
        #         ret = max(ret, F(i + 1, True) - prices[i] - fee)
        #     mem[(i, hold)] = ret
        #     return ret
        # return F(0, False)

        dp = [[0 for _ in range(n + 1)] for _ in range(2)]
        for i in range(n - 1, -1, -1):
            # not holding
            dp[0][i] = max(dp[0][i + 1], dp[1][i + 1] - prices[i] - fee)
            # holding
            dp[1][i] = max(dp[1][i + 1], dp[0][i + 1] + prices[i])
        return dp[0][0]