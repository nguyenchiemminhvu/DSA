class Solution:
    def checkPowersOfThree(self, n: int) -> bool:
        coins = []
        candidate = 1
        while candidate <= n:
            coins.append(candidate)
            candidate *= 3
        
        m = len(coins)

        # knapsack problem
        def F(i: int, s: int) -> bool:
            if s == 0:
                return True
            if i <= 0 and s != 0:
                return False
            res = F(i - 1, s)
            if coins[i - 1] <= s:
                res = res or F(i - 1, s - coins[i - 1])
            return res
        return F(m, n)

        # dp = [[False] * (n + 1) for _ in range(m + 1)]
        # for i in range(m + 1):
        #     dp[i][0] = True
        # for i in range(1, m + 1):
        #     for s in range(1, n + 1):
        #         dp[i][s] = dp[i - 1][s]
        #         if coins[i - 1] <= s:
        #             dp[i][s] = dp[i][s] or dp[i - 1][s - coins[i - 1]]
        # return dp[m][n]