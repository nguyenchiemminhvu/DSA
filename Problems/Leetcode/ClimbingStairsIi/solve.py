from typing import List

class Solution:
    def climbStairs(self, n: int, costs: List[int]) -> int:
        costs = [0] + costs
        
        # mem = {}
        # def F(i: int) -> int:
        #     if i < 0:
        #         return 0
        #     if i == 0:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     res = float('inf')
        #     if i - 1 >= 0:
        #         res = min(res, F(i - 1) + costs[i] + 1)
        #     if i - 2 >= 0:
        #         res = min(res, F(i - 2) + costs[i] + 4)
        #     if i - 3 >= 0:
        #         res = min(res, F(i - 3) + costs[i] + 9)
        #     mem[i] = res
        #     return res
        # return F(n)

        dp = [float('inf')] * (n + 1)
        dp[0] = 0
        for i in range(n + 1):
            if i - 1 >= 0:
                dp[i] = min(dp[i], dp[i - 1] + costs[i] + 1)
            if i - 2 >= 0:
                dp[i] = min(dp[i], dp[i - 2] + costs[i] + 4)
            if i - 3 >= 0:
                dp[i] = min(dp[i], dp[i - 3] + costs[i] + 9)
        return dp[n]