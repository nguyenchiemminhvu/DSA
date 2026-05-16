from typing import List

class Solution:
    def validPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        
        # mem = {}
        # def F(i: int) -> bool:
        #     if i < 0:
        #         return True
        #     if i in mem:
        #         return mem[i]
        #     res = True
        #     op1 = op2 = op3 = False
        #     if i - 1 >= 0 and nums[i] == nums[i - 1]:
        #         op1 = F(i - 2)
        #     if i - 2 >= 0 and nums[i] == nums[i - 1] and nums[i - 1] == nums[i - 2]:
        #         op2 = F(i - 3)
        #     if i - 2 >= 0 and nums[i] == nums[i - 1] + 1 and nums[i - 1] == nums[i - 2] + 1:
        #         op3 = F(i - 3)
        #     res = op1 or op2 or op3
        #     mem[i] = res
        #     return res
        # return F(n - 1)

        dp = [True] * n
        for i in range(n):
            op1 = op2 = op3 = False
            if i - 1 >= 0 and nums[i] == nums[i - 1]:
                op1 = dp[i - 2]
            if i - 2 >= 0 and nums[i] == nums[i - 1] and nums[i - 1] == nums[i - 2]:
                op2 = dp[i - 3]
            if i - 2 >= 0 and nums[i] == nums[i - 1] + 1 and nums[i - 1] == nums[i - 2] + 1:
                op3 = dp[i - 3]
            dp[i] = op1 or op2 or op3
        return dp[n - 1]