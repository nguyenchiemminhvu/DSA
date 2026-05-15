class Solution:
    def integerBreak(self, n: int) -> int:
        # mem = {}
        # def F(i: int, splitted: bool) -> int:
        #     if i == 1:
        #         return 1
        #     if i in mem:
        #         return mem[i]
        #     prod = i if splitted else 1
        #     l, r = 1, i - 1
        #     while l <= r:
        #         prod = max(
        #             prod,
        #             l * r,
        #             F(l, True) * r,
        #             l * F(r, True),
        #             F(l, True) * F(r, True)
        #         )
        #         l += 1
        #         r -= 1
        #     mem[i] = prod
        #     return prod
        # return F(n, False)

        dp = [[0 for _ in range(2)] for _ in range(n + 1)]
        dp[1][0] = dp[1][1] = 1
        for i in range(2, n + 1):
            for splitted in range(2):
                dp[i][splitted] = i if splitted == 1 else 1
                l, r = 1, i - 1
                while l <= r:
                    dp[i][splitted] = max(
                        dp[i][splitted],
                        l * r,
                        dp[l][1] * r,
                        l * dp[r][1],
                        dp[l][1] * dp[r][1]
                    )
                    l += 1
                    r -= 1
        return dp[n][False]