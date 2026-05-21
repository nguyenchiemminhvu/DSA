from typing import List

class Solution:
    def maximumProfit(self, prices: List[int], k: int) -> int:
        n = len(prices)
        INF = float('-inf')

        # state = 0 means can do any operation buy or sell
        #   -> 0 to 1: to buy, must sell to be 0 again
        #   -> 0 to 2: to sell, must buy to be 0 again
        # from functools import lru_cache
        # @lru_cache(None)
        # def F(i: int, t: int, state: int) -> int:
        #     if i >= n:
        #         return 0 if state == 0 else INF
        #     res = F(i + 1, t, state)
        #     if state == 0:
        #         res = max(
        #             res,
        #             -prices[i] + F(i + 1, t, 1),
        #             prices[i] + F(i + 1, t, 2)
        #         )
        #     elif state == 1: # holding stock
        #         if t < k:
        #             res = max(
        #                 res,
        #                 prices[i] + F(i + 1, t + 1, 0)
        #             )
        #     elif state == 2: # on sell first
        #         if t < k:
        #             res = max(
        #                 res,
        #                 -prices[i] + F(i + 1, t + 1, 0)
        #             )
        #     return res
        # return F(0, 0, 0)

        dp = [[[INF] * 3 for _ in range(k + 1)] for _ in range(n + 1)]
        for t in range(k + 1):
            dp[n][t][0] = 0
        for i in range(n - 1, -1, -1):
            for t in range(k, -1, -1):
                for state in range(3):
                    dp[i][t][state] = dp[i + 1][t][state]
                    if state == 0:
                        dp[i][t][state] = max(
                            dp[i][t][state],
                            -prices[i] + dp[i + 1][t][1],
                            prices[i] + dp[i + 1][t][2]
                        )
                    elif state == 1:
                        if t < k:
                            dp[i][t][state] = max(
                                dp[i][t][state],
                                prices[i] + dp[i + 1][t + 1][0]
                            )
                    elif state == 2:
                        if t < k:
                            dp[i][t][state] = max(
                                dp[i][t][state],
                                -prices[i] + dp[i + 1][t + 1][0]
                            )
        return dp[0][0][0]