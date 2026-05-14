from typing import List

class Solution:
    def findLongestChain(self, pairs: List[List[int]]) -> int:
        pairs.sort(key=lambda x: (x[0], x[1]))
        n = len(pairs)

        # mem = {}
        # def F(i: int) -> int:
        #     if i >= n:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     op1 = F(i + 1) # just skip this one
        #     j = i + 1
        #     while j < n and pairs[j][0] <= pairs[i][1]:
        #         j += 1
        #     op2 = 1 + F(j) # pick the current and next possibility
        #     res = max(op1, op2)
        #     mem[i] = res
        #     return res
        # return F(0)

        dp = [0] * (n + 1)
        for i in range(n - 1, -1, -1):
            op1 = dp[i + 1]
            j = i + 1
            while j < n and pairs[j][0] <= pairs[i][1]:
                j += 1
            op2 = 1 + dp[j]
            dp[i] = max(op1, op2)
        return dp[0]