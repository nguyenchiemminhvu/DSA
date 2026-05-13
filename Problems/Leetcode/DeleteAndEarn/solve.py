from collections import defaultdict
from typing import List

class Solution:
    def deleteAndEarn(self, nums: List[int]) -> int:
        n = len(nums)

        max_val = max(nums)
        s = defaultdict(int)
        for val in nums:
            s[val] += val
        
        # mem = {}
        # def F(i: int) -> int:
        #     if i <= 0:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     res = max(
        #         s[i] + F(i - 2),
        #         F(i - 1)
        #     )
        #     mem[i] = res
        #     return res
        # return F(max_val)

        dp = [0] * (max_val + 1)
        for i in range(1, max_val + 1):
            dp[i] = max(dp[i], dp[i - 1], s[i] + (0 if i - 2 < 0 else dp[i - 2]))
        return dp[max_val]