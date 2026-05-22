from typing import List

class Solution:
    def largestDivisibleSubset(self, nums: List[int]) -> List[int]:
        nums.sort()
        n = len(nums)

        dp = [1] * n
        parent = [-1] * n
        max_dp = 1
        max_dp_idx = 0
        for i in range(n):
            for j in range(i):
                if nums[i] % nums[j] == 0:
                    if dp[i] < 1 + dp[j]:
                        dp[i] = 1 + dp[j]
                        parent[i] = j
            if max_dp < dp[i]:
                max_dp = dp[i]
                max_dp_idx = i
        
        res = []
        while max_dp_idx != -1:
            res.append(nums[max_dp_idx])
            max_dp_idx = parent[max_dp_idx]
        return res