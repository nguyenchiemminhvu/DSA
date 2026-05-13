from typing import List

class Solution:
    def maxProfit(self, k: int, prices: List[int]) -> int:
        n = len(prices)

        # mem = {}
        # def F(i: int, hold: bool, times: int) -> int:
        #     if i >= n:
        #         return 0
        #     if times >= k:
        #         return 0
        #     if (i, hold, times) in mem:
        #         return mem[(i, hold, times)]
        #     res = 0
        #     if not hold:
        #         res = max(res,
        #                 -prices[i] + F(i + 1, True, times), # pick this stock
        #                 F(i + 1, False, times) # skip this stock
        #             )
        #     else:
        #         res = max(res,
        #                 prices[i] + F(i + 1, False, times + 1), # sell this stock
        #                 F(i + 1, True, times) # keep holding
        #             )
        #     mem[(i, hold, times)] = res
        #     return res
        
        # return F(0, False, 0)

        dp = [[[0] * (k + 1) for _ in range(2)] for _ in range(n + 1)] # dp[i][hold][times]
        # dp[n][...][...] = 0 already
        # dp[i][...][k] = 0 already
        for i in range(n - 1, -1, -1):
            for times in range(k - 1, -1, -1):
                if times >= k:
                    dp[i][0][times] = 0
                    dp[i][1][times] = 0
                else:
                    # not holding
                    dp[i][0][times] = max(
                        dp[i][1][times],
                        -prices[i] + dp[i + 1][1][times], # pick this stock
                        dp[i + 1][0][times] # skip this stock
                    )
                    # holding
                    dp[i][1][times] = max(
                        dp[i][0][times],
                        prices[i] + dp[i + 1][0][times + 1], # sell this stock
                        dp[i + 1][1][times] # keep holding
                    )
        return dp[0][0][0]