from typing import List

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)

        # mem = {}
        # def F(i: int, hold: bool) -> int:
        #     if i >= n:
        #         return 0
        #     if (i, hold) in mem:
        #         return mem[(i, hold)]
        #     res = 0
        #     if not hold:
        #         res = max(
        #                 res,
        #                 -prices[i] + F(i + 1, True), # buy this stock
        #                 F(i + 1, False) # skip this day
        #         )
        #     else:
        #         res = max(
        #                 res,
        #                 prices[i] + F(i + 2, False), # sell this stock
        #                 F(i + 1, True)
        #         )
        #     mem[(i, hold)] = res
        #     return res
        # return F(0, False)

        dp = [[0] * 2 for _ in range(n + 2)]
        # dp[n][...] already set to 0
        for i in range(n - 1, -1, -1):
            # not holding
            dp[i][0] = max(
                -prices[i] + dp[i + 1][1],
                dp[i + 1][0]
            )
            # holding
            dp[i][1] = max(
                prices[i] + dp[i + 2][0],
                dp[i + 1][1]
            )
        return dp[0][0]