from typing import List

class Solution:
    def rob(self, nums: List[int]) -> int:
        n = len(nums)

        # mem = {}
        # def F(i: int) -> int:
        #     if i >= n:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     max_robbed = 0
        #     max_robbed = max(max_robbed, nums[i] + F(i + 2)) # pick this house
        #     max_robbed = max(max_robbed, F(i + 1)) # skip this house
        #     mem[i] = max_robbed
        #     return max_robbed
        # return F(0)

        dp = [0] * (n + 2)
        for i in range(n - 1, -1, -1):
            dp[i] = max(nums[i] + dp[i + 2], dp[i + 1])
        return dp[0]