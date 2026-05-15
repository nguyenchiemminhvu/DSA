class Solution:
    def countVowelStrings(self, n: int) -> int:
        opts = ['a', 'e', 'i', 'o', 'u']
        no = len(opts)

        # mem = {}
        # def F(i: int, io: int) -> int:
        #     if i >= n:
        #         return 1
        #     if io >= no:
        #         return 0
        #     if (i, io) in mem:
        #         return mem[(i, io)]
        #     ways = F(i, io + 1)
        #     ways += F(i + 1, io)
        #     mem[(i, io)] = ways
        #     return ways
        # return F(0, 0)

        dp = [[0] * (no + 1) for _ in range(n + 1)]
        for i in range(no + 1):
            dp[n][i] = 1
        for i in range(n - 1, -1, -1):
            for io in range(no - 1, -1, -1):
                dp[i][io] += dp[i][io + 1] + dp[i + 1][io]
        return dp[0][0]