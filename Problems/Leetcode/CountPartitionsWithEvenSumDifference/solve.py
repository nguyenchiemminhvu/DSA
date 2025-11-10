from typing import List

class Solution:
    def countPartitions(self, nums: List[int]) -> int:
        n = len(nums)
        for i in range(1, n):
            nums[i] += nums[i - 1]
        
        res = 0
        for i in range(n - 1):
            left = nums[i]
            right = nums[-1] - nums[i]
            if (left - right) % 2 == 0:
                res += 1
        return res