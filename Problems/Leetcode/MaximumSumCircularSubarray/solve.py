from typing import List

class Solution:
    def maxSubarraySumCircular(self, nums: List[int]) -> int:
        n = len(nums)
        cur_max = nums[0]
        cur_min = nums[0]
        ka_max = nums[0]
        ka_min = nums[0]
        for i in range(1, n):
            cur_max = max(nums[i], cur_max + nums[i])
            ka_max = max(ka_max, cur_max)
            cur_min = min(nums[i], cur_min + nums[i])
            ka_min = min(ka_min, cur_min)
        
        if ka_max < 0:
            return max(nums)
        
        return max(ka_max, sum(nums) - ka_min)