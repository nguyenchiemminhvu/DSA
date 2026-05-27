class Solution:
    def numWays(self, steps: int, n: int) -> int:
        mod = 10**9 + 7

        # mem = {}
        # def F(i: int, k: int) -> int:
        #     if i < 0 or i >= n:
        #         return 0
        #     if k < 0:
        #         return 0
        #     if i == 0 and k == 0:
        #         return 1
        #     if (i, k) in mem:
        #         return mem[(i, k)]
        #     res = 0
        #     for j in range(i - 1, i + 2):
        #         if j >= 0 and j < n:
        #             res = ((res % mod) + (F(j, k - 1) % mod)) % mod
        #     mem[(i, k)] = res
        #     return res
        # return F(0, steps)

        m = min(n, steps // 2 + 1)
        dp = [0] * m
        dp[0] = 1
        for _ in range(steps):
            nxt = [0] * m
            for i in range(m):
                nxt[i] = (nxt[i] + dp[i]) % mod          # stay
                if i - 1 >= 0:
                    nxt[i - 1] = (nxt[i - 1] + dp[i]) % mod  # left
                if i + 1 < m:
                    nxt[i + 1] = (nxt[i + 1] + dp[i]) % mod  # right
            dp = nxt

        return dp[0]