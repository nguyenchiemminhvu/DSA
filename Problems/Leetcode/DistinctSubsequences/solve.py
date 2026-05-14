from typing import List

class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        ns, nt = len(s), len(t)
        
        # mem = {}
        # def F(i: int, it: int) -> int:
        #     if it >= nt:
        #         return 1
        #     if i >= ns:
        #         return 0
        #     if (i, it) in mem:
        #         return mem[(i, it)]
        #     count = 0
        #     if s[i] == t[it]:
        #         count += F(i + 1, it + 1)
        #     count += F(i + 1, it)
        #     mem[(i, it)] = count
        #     return count
        # return F(0, 0)

        dp = [[0 for _ in range(nt + 1)] for _ in range(ns + 1)]
        for i in range(ns + 1):
            dp[i][nt] = 1
        
        for i in range(ns - 1, -1, -1):
            for it in range(nt - 1, -1, -1):
                dp[i][it] += dp[i + 1][it]
                if s[i] == t[it]:
                    dp[i][it] += dp[i + 1][it + 1]
        return dp[0][0]