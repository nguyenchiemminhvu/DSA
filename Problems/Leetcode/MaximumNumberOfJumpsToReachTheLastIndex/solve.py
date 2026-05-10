from typing import List

class Solution:
    def maximumJumps(self, nums: List[int], target: int) -> int:
        n = len(nums)

        # mem = {}
        # def F(i: int, jumps: int) -> int:
        #     if i == n - 1:
        #         return jumps
            
        #     if (i, jumps) in mem:
        #         return mem[(i, jumps)]
            
        #     max_jumps = -1
        #     for j in range(i + 1, n):
        #         if abs(nums[j] - nums[i]) <= target:
        #             max_jumps = max(max_jumps, F(j, jumps + 1))
            
        #     mem[(i, jumps)] = max_jumps
        #     return max_jumps
        # return F(0, 0)

        dp = [-1] * n
        dp[0] = 0
        for i in range(n - 1):
            if dp[i] == -1:
                continue
            for j in range(i + 1, n):
                if abs(nums[j] - nums[i]) <= target:
                    dp[j] = max(dp[j], dp[i] + 1)
        return dp[n - 1]