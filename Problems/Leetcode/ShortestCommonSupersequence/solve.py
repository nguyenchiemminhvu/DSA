class Solution:
    def shortestCommonSupersequence(self, s1: str, s2: str) -> str:
        n1, n2 = len(s1), len(s2)

        dp = [[0 for _ in range(n2 + 1)] for _ in range(n1 + 1)]
        for i1 in range(1, n1 + 1):
            c1 = s1[i1 - 1]
            for i2 in range(1, n2 + 1):
                c2 = s2[i2 - 1]
                if c1 == c2:
                    dp[i1][i2] = max(dp[i1][i2], 1 + dp[i1 - 1][i2 - 1])
                else:
                    dp[i1][i2] = max(dp[i1][i2], dp[i1 - 1][i2], dp[i1][i2 - 1])
        
        res = []
        i1, i2 = n1, n2
        while i1 > 0 and i2 > 0:
            if s1[i1 - 1] == s2[i2 - 1]:
                res.append(s1[i1 - 1])
                i1 -= 1
                i2 -= 1
            else:
                if dp[i1 - 1][i2] > dp[i1][i2 - 1]:
                    res.append(s1[i1 - 1])
                    i1 -= 1
                else:
                    res.append(s2[i2 - 1])
                    i2 -= 1
        
        while i1 > 0:
            res.append(s1[i1 - 1])
            i1 -= 1
        
        while i2 > 0:
            res.append(s2[i2 - 1])
            i2 -= 1

        res.reverse()
        return "".join(res)