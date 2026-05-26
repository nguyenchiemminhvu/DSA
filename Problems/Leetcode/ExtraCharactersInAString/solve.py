from typing import List

class Solution:
    def minExtraChar(self, s: str, words: List[str]) -> int:
        n = len(s)

        # mem = {}
        # def F(i: int) -> int:
        #     if i < 0:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     res = i + 1
        #     for word in words:
        #         nw = len(word)
        #         if i - nw + 1 >= 0 and s[i - nw + 1: i + 1] == word:
        #             res = min(res, F(i - nw))
        #         else:
        #             res = min(res, 1 + F(i - 1))
        #     mem[i] = res
        #     return res
        # return F(n - 1)

        dp = [i + 1 for i in range(n)]
        for i in range(n):
            for word in words:
                nw = len(word)
                if i - nw + 1 >= 0 and s[i - nw + 1: i + 1] == word:
                    dp[i] = min(dp[i], dp[i - nw] if i - nw >= 0 else 0)
                else:
                    dp[i] = min(dp[i], 1 + (dp[i - 1] if i - 1 >= 0 else 0))
        return dp[n - 1]