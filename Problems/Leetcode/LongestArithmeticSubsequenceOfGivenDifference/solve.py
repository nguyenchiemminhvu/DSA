from collections import defaultdict
from typing import List

class Solution:
    def longestSubsequence(self, arr: List[int], diff: int) -> int:
        n = len(arr)
        
        # ---------------------------------
        # mem = {}
        # def F(i: int) -> int:
        #     if i < 0:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     res = 1
        #     for j in range(i):
        #         if arr[i] - arr[j] == diff:
        #             res = max(res, 1 + F(j))
        #     mem[i] = res
        #     return res
        # res = 1
        # dp = [1] * n
        # for i in range(n):
        #     res = max(res, F(i))
        # return res

        # ----------------------------------
        # res = 1
        # dp = [1] * n
        # for i in range(n):
        #     for j in range(i):
        #         if arr[i] - arr[j] == diff:
        #             dp[i] = max(dp[i], 1 + dp[j])
        #             res = max(res, dp[i])
        # return res

        # ----------------------------------
        res = 1
        dp = defaultdict(int)
        for val in arr:
            prev = val - diff
            dp[val] = 1 + dp[prev]
            res = max(res, dp[val])
        return res