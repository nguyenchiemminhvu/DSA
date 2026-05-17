class Solution:
    def minDistance(self, s1: str, s2: str) -> int:
        n1, n2 = len(s1), len(s2)

        # mem = {}
        # def F(i1: int, i2: int) -> int:
        #     if i1 < 0:
        #         return i2 + 1
        #     if i2 < 0:
        #         return i1 + 1
        #     if (i1, i2) in mem:
        #         return mem[(i1, i2)]
        #     res = float('inf')
        #     if s1[i1] == s2[i2]:
        #         res = min(
        #             res,
        #             F(i1 - 1, i2 - 1)
        #         )
        #     else:
        #         res = min(
        #             res,
        #             1 + F(i1 - 1, i2),
        #             1 + F(i1, i2 - 1)
        #         )
        #     mem[(i1, i2)] = res
        #     return res
        # return F(n1 - 1, n2 - 1)

        dp = [[float('inf')] * (n2 + 1) for _ in range(n1 + 1)]
        dp[n1][n2] = 0
        for i1 in range(n1):
            dp[i1][n2] = n1 - i1
        for i2 in range(n2):
            dp[n1][i2] = n2 - i2

        for i1 in range(n1 - 1, -1, -1):
            for i2 in range(n2 - 1, -1, -1):
                if s1[i1] == s2[i2]:
                    dp[i1][i2] = min(dp[i1][i2], dp[i1+1][i2+1])
                else:
                    dp[i1][i2] = min(
                        dp[i1][i2],
                        1 + dp[i1 + 1][i2],
                        1 + dp[i1][i2 + 1]
                    )
        return dp[0][0]