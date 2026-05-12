from typing import List

class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        nc = len(coins)

        # mem = {}
        # def F(i: int) -> int:
        #     if i < 0:
        #         return float('inf')
        #     if i == 0:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     res = float('inf')
        #     for coin in coins:
        #         if coin <= i:
        #             opt = F(i - coin)
        #             if opt != float('inf'):
        #                 res = min(res, 1 + opt)
        #     mem[i] = res
        #     return res
        # res = F(amount)
        # return -1 if res == float('inf') else res

        dp = [float('inf')] * (amount + 1)
        dp[0] = 0
        for i in range(amount + 1):
            for coin in coins:
                if coin <= i and dp[i - coin] != float('inf'):
                    dp[i] = min(dp[i], 1 + dp[i - coin])
        return -1 if dp[amount] == float('inf') else dp[amount]