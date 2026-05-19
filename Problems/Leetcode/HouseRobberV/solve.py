from typing import List

class Solution:
    def rob(self, nums: List[int], colors: List[int]) -> int:
        n = len(nums)
        
        # mem = {}
        # def F(i: int) -> int:
        #     if i < 0:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     res = 0
        #     if i - 1 >= 0 and colors[i] != colors[i - 1]:
        #         res = nums[i] + F(i - 1)
        #     else:
        #         res = max(
        #             F(i - 1),
        #             nums[i] + F(i - 2)
        #         )
        #     mem[i] = res
        #     return res
        # return F(n - 1)

        dp = nums[:]
        for i in range(n):
            if i - 1 >= 0 and colors[i] != colors[i - 1]:
                dp[i] = nums[i] + dp[i - 1]
            else:
                dp[i] = max(
                    dp[i - 1] if i - 1 >= 0 else 0,
                    nums[i] + (dp[i - 2] if i - 2 >= 0 else 0)
                )
        return dp[n - 1]