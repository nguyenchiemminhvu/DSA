from typing import List

class Solution:
    def mostPoints(self, questions: List[List[int]]) -> int:
        n = len(questions)

        # mem = {}
        # def F(i: int) -> int:
        #     if i >= n:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     res = F(i + 1)
        #     res = max(res, questions[i][0] + F(i + questions[i][1] + 1))
        #     mem[i] = res
        #     return res
        # return F(0)

        dp = [0 for _ in range(n + 1)]
        for i in range(n - 1, -1, -1):
            if i + questions[i][1] + 1 <= n:
                dp[i] = max(dp[i], questions[i][0] + dp[i + questions[i][1] + 1])
            else:
                dp[i] = max(dp[i], questions[i][0])
            dp[i] = max(dp[i], dp[i + 1])
        return dp[0]