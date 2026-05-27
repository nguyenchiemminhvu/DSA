class Solution:
    def peopleAwareOfSecret(self, n: int, delay: int, forget: int) -> int:
        mod = 10**9 + 7

        # mem = {}
        # def F(i: int) -> int:
        #     if i <= 0:
        #         return 0
        #     if i == 1:
        #         return 1
        #     if i in mem:
        #         return mem[i]
        #     res = 0
        #     left_idx = i - forget + 1
        #     right_idx = i - delay
        #     for j in range(left_idx, right_idx + 1):
        #         res += F(j) % mod
        #         res %= mod
        #     mem[i] = res
        #     return res
        # res = 0
        # for i in range(n - forget + 1, n + 1):
        #     res += F(i) % mod
        # return res % mod

        dp = [0] * (n + 1)
        dp[1] = 1
        for i in range(2, n + 1):
            left = i - forget + 1
            right = i - delay
            for j in range(left, right + 1):
                if j >= 0:
                    dp[i] += dp[j] % mod
                    dp[i] %= mod
        
        return sum(dp[n - forget + 1:n + 1]) % mod