from typing import List

class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        s = sum(nums)
        if s & 1:
            return False
        half = s // 2

        # mem = {}
        # def F(i: int, amount: int) -> bool:
        #     if i >= n:
        #         return amount == 0
            
        #     if (i, amount) in mem:
        #         return mem[(i, amount)]
            
        #     res = False
        #     if nums[i] > amount:
        #         res = F(i + 1, amount)
        #     else:
        #         res = F(i + 1, amount) or F(i + 1, amount - nums[i])
        #     mem[(i, amount)] = res
        #     return res
        
        # return F(0, half)

        dp = [[False for _ in range(half + 1)] for _ in range(n + 1)]
        dp[n][0] = True
        
        for i in range(n - 1, -1, -1):
            for amount in range(half + 1):
                if nums[i] > amount:
                    dp[i][amount] = dp[i + 1][amount]
                else:
                    dp[i][amount] = dp[i + 1][amount] or dp[i + 1][amount - nums[i]]
        
        return dp[0][half]