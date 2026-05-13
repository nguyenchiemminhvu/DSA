from typing import List

class Solution:
    def longestValidParentheses(self, s: str) -> int:
        n = len(s)
        
        # mem = {}
        # def F(i: int) -> int:
        #     if i <= 0:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     length = 0
        #     if s[i] == ')':
        #         if s[i - 1] == '(':
        #             return 2 + F(i - 2)
        #         else:
        #             prev_length = F(i - 1)
        #             prev_idx = i - prev_length - 1
        #             if prev_length > 0 and prev_idx >= 0 and s[prev_idx] == '(':
        #                 length = 2 + prev_length + F(prev_idx - 1)
        #     mem[i] = length
        #     return length
        # res = 0
        # for i in range(n):
        #     res = max(res, F(i))
        # return res

        res = 0
        dp = [0] * n
        for i in range(1, n):
            if s[i] == ')':
                if s[i - 1] == '(':
                    dp[i] = 2 + (dp[i - 2] if i - 2 >= 0 else 0)
                else:
                    prev = dp[i - 1]
                    j = i - prev - 1
                    if j >= 0 and s[j] == '(':
                        dp[i] = 2 + prev + (dp[j - 1] if j - 1 >= 0 else 0)
            res = max(res, dp[i])
        return res