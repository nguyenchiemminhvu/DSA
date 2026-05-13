from typing import List

class Solution:
    def longestPalindromeSubseq(self, s: str) -> int:
        n = len(s)

        # mem = {}
        # def F(l: int, r: int) -> int:
        #     if l > r:
        #         return 0
        #     if l == r:
        #         return 1
        #     if (l, r) in mem:
        #         return mem[(l, r)]
        #     res = 0
        #     if s[l] == s[r]:
        #         res = 2 + F(l + 1, r - 1)
        #     else:
        #         res = max(F(l + 1, r), F(l, r - 1))
        #     mem[(l, r)] = res
        #     return res
        # return F(0, n - 1)

        dp = [[0 for _ in range(n)] for _ in range(n)]
        for l in range(n - 1, -1, -1):
            for r in range(n):
                if l > r:
                    dp[l][r] = 0
                elif l == r:
                    dp[l][r] = 1
                else:
                    if s[l] == s[r]:
                        dp[l][r] = max(dp[l][r], 2 + dp[l + 1][r - 1])
                    else:
                        dp[l][r] = max(dp[l][r], dp[l + 1][r], dp[l][r - 1])
        return dp[0][n - 1]