from collections import defaultdict
from typing import List

class Solution:
    def longestArithSeqLength(self, nums: List[int]) -> int:
        n = len(nums)

        # mem = {}
        # def F(i: int, diff: int) -> int:
        #     if i < 0:
        #         return 0
        #     if (i, diff) in mem:
        #         return mem[(i, diff)]
        #     res = 1
        #     for j in range(i-1, -1, -1):
        #         if nums[i] - nums[j] == diff:
        #             res = max(res, 1 + F(j, diff))
        #     mem[(i, diff)] = res
        #     return res
        
        res = 0

        dp = [defaultdict(int) for _ in range(n)]
        for i in range(n):
            for j in range(i):
                diff = nums[i] - nums[j]
                # res = max(res, F(i, diff))

                if diff not in dp[j]:
                    dp[i][diff] = 2
                else:
                    dp[i][diff] = max(dp[i][diff], dp[j][diff] + 1)
                
                res = max(res, dp[i][diff])
        return res