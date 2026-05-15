class Solution:
    def minCost(self, n: int) -> int:
        # --------------------------------------
        # mem = {}
        # def F(i: int) -> int:
        #     if i <= 1:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     l, r = 1, i - 1
        #     cost = float('inf')
        #     while l <= r:
        #         cost = min(cost, (l * r) + F(l) + F(r))
        #         l += 1
        #         r -= 1
        #     mem[i] = cost
        #     return cost
        # return F(n)

        # ---------------------------------------
        # dp = [float('inf') for _ in range(n + 1)]
        # dp[0] = dp[1] = 0
        # for i in range(2, n + 1):
        #     l, r = 1, i - 1
        #     while l <= r:
        #         dp[i] = min(dp[i], (l * r) + dp[l] + dp[r])
        #         l += 1
        #         r -= 1
        # return dp[n]

        # --------------------------------------
        # dp = [float('inf') for _ in range(n + 1)]
        # dp[0] = dp[1] = 0
        # for i in range(2, n + 1):
        #     l, r = 1, i - 1
        #     dp[i] = min(dp[i], (l * r) + dp[l] + dp[r])
        # return dp[n]

        # ----------------------------------------
        # res = 0
        # for i in range(n):
        #     res += i
        # return res

        # --------------------------------------
        return n * (n - 1) // 2