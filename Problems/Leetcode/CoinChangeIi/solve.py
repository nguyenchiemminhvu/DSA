from typing import List

class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        n = len(coins)
        coins.sort(reverse=True)

        # mem = {}
        # def F(i: int, amount: int) -> int:
        #     if amount < 0:
        #         return 0
        #     if amount == 0:
        #         return 1
        #     if i >= n:
        #         return 0
        #     if (i, amount) in mem:
        #         return mem[(i, amount)]
        #     ways = F(i + 1, amount)
        #     ways += F(i, amount - coins[i])
        #     mem[(i, amount)] = ways
        #     return ways
        # return F(0, amount)

        dp = [[0 for _ in range(amount + 1)] for _ in range(n + 1)]
        for i in range(n + 1):
            dp[i][0] = 1
        for i in range(n - 1, -1, -1):
            for a in range(amount + 1):
                dp[i][a] = dp[i + 1][a]
                if coins[i] <= a:
                    dp[i][a] += dp[i][a - coins[i]]
        return dp[0][amount]