from typing import List

class Solution:
    def isInterleave(self, s1: str, s2: str, t: str) -> bool:
        n1, n2, nt = len(s1), len(s2), len(t)
        if n1 + n2 != nt:
            return False
        
        # mem = {}
        # def F(i1: int, i2: int) -> bool:
        #     if i1 >= n1:
        #         return s2[i2:] == t[n1 + i2:]
        #     if i2 >= n2:
        #         return s1[i1:] == t[n2 + i1:]
        #     if (i1, i2) in mem:
        #         return mem[(i1, i2)]
        #     res = False
        #     if s1[i1] == t[i1 + i2]:
        #         res = res or F(i1 + 1, i2)
        #     if s2[i2] == t[i1 + i2]:
        #         res = res or F(i1, i2 + 1)
        #     mem[(i1, i2)] = res
        #     return res
        # return F(0, 0)

        dp = [[False for _ in range(n2 + 1)] for _ in range(n1 + 1)]
        for i2 in range(n2 + 1):
            dp[n1][i2] = (s2[i2:] == t[n1 + i2:])
        for i1 in range(n1 + 1):
            dp[i1][n2] = (s1[i1:] == t[n2 + i1:])
        for i1 in range(n1 - 1, -1, -1):
            for i2 in range(n2 - 1, -1, -1):
                op1, op2 = False, False
                if s1[i1] == t[i1 + i2]:
                    op1 = op1 or dp[i1 + 1][i2]
                if s2[i2] == t[i1 + i2]:
                    op2 = op2 or dp[i1][i2 + 1]
                dp[i1][i2] = op1 or op2
        return dp[0][0]