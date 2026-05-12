from typing import List

class Solution:
    def wordBreak(self, s: str, words: List[str]) -> bool:
        n = len(s)

        # mem = {}
        # def F(i: int) -> bool:
        #     if i > n:
        #         return False
        #     if i == n:
        #         return True
        #     if i in mem:
        #         return mem[i]
        #     for word in words:
        #         nw = len(word)
        #         if i + nw <= n and s[i:i + nw] == word:
        #             if F(i + nw):
        #                 mem[i] = True
        #                 return True
        #     mem[i] = False
        #     return False
        # return F(0)

        dp = [False] * (n + 1001)
        dp[n] = True
        for i in range(n-1, -1, -1):
            for word in words:
                nw = len(word)
                if dp[i + nw] and s[i:i + nw] == word:
                    dp[i] = True
        return dp[0]