from typing import List

class Solution:
    def longestStrChain(self, words: List[str]) -> int:
        n = len(words)
        words.sort(key=lambda x: len(x))

        def is_pred(a: str, b: str) -> bool:
            na, nb = len(a), len(b)
            ia, ib = 0, 0
            while ia < na and ib < nb:
                if a[ia] == b[ib]:
                    ia += 1
                ib += 1
            return ia == na

        # mem = {}
        # def F(i: int) -> int:
        #     if i < 0:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     res = 1
        #     for j in range(i):
        #         if len(words[j]) + 1 == len(words[i]):
        #             if (is_pred(words[j], words[i])):
        #                 res = max(res, 1 + F(j))
        #     mem[i] = res
        #     return res
        # res = 1
        # for i in range(n):
        #     res = max(res, F(i))
        # return res

        dp = [1] * n
        res = 1
        for i in range(n):
            for j in range(i):
                if len(words[j]) + 1 == len(words[i]):
                    if is_pred(words[j], words[i]):
                        dp[i] = max(dp[i], 1 + dp[j])
            res = max(res, dp[i])
        return res