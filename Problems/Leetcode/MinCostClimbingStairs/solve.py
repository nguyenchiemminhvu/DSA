from typing import List

class Solution:
    def minCostClimbingStairs(self, cost: List[int]) -> int:
        n = len(cost)
        memo = {}
        def F(i: int) -> int:
            if i >= n:
                return 0
            if i in memo:
                return memo[i]
            memo[i] = min(cost[i] + F(i + 1), cost[i] + F(i + 2))
            return memo[i]
        
        # return min(F(0), F(1))

        def DP(i: int) -> int:
            dp = [0] * (n + 2)
            for j in range(n - 1, -1, -1):
                dp[j] = min(cost[j] + dp[j + 1], cost[j] + dp[j + 2])
            return dp[i]
        
        return min(DP(0), DP(1))