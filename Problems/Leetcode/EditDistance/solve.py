class Solution:
    def minDistance(self, s1: str, s2: str) -> int:
        n1 = len(s1)
        n2 = len(s2)

        # mem = {}
        # def F(i1: int, i2: int) -> int:
        #     if i1 >= n1:
        #         return max(0, n2 - i2) # need insert operations
        #     if i2 >= n2:
        #         return max(0, n1 - i1) # need delete operations

        #     if (i1, i2) in mem:
        #         return mem[(i1, i2)]

        #     res = float('inf')
        #     if s1[i1] == s2[i2]:
        #         res = F(i1 + 1, i2 + 1)
        #     else:
        #         op1 = 1 + F(i1 + 1, i2 + 1) # move on with sub operation
        #         op2 = 1 + F(i1, i2 + 1) # move on with ins operation
        #         op3 = 1 + F(i1 + 1, i2) # move on with del operation
        #         res = min([op1, op2, op3])
        #     mem[(i1, i2)] = res
        #     return res
        
        # return F(0, 0)

        dp = [[float('inf') for _ in range(n2 + 1)] for _ in range(n1 + 1)]
        for i in range(n1 + 1):
            dp[i][n2] = n1 - i
        for i in range(n2 + 1):
            dp[n1][i] = n2 - i
        
        for i1 in range(n1 - 1, -1, -1):
            for i2 in range(n2 - 1, -1, -1):
                if s1[i1] == s2[i2]:
                    dp[i1][i2] = dp[i1 + 1][i2 + 1]
                else:
                    dp[i1][i2] = min([
                        1 + dp[i1 + 1][i2 + 1],
                        1 + dp[i1][i2 + 1],
                        1 + dp[i1 + 1][i2]
                    ])
        
        return dp[0][0]