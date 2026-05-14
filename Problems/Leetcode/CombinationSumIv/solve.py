from typing import List

class Solution:
    def combinationSum4(self, nums: List[int], target: int) -> int:
        n = len(nums)

        # mem = {}
        # def F(amount: int) -> int:
        #     if amount < 0:
        #         return 0
        #     if amount == 0:
        #         return 1
        #     if amount in mem:
        #         return mem[amount]
        #     ways = 0
        #     for i in range(n):
        #         ways += F(amount - nums[i])
        #     mem[amount] = ways
        #     return ways
        # return F(target)

        dp = [0 for _ in range(target + 1)]
        dp[0] = 1
        for amount in range(target + 1):
            for i in range(n):
                if nums[i] <= amount:
                    dp[amount] += dp[amount - nums[i]]
        return dp[target]