from typing import List

class Solution:
    def minStartValue(self, nums: List[int]) -> int:
        n = len(nums)
        for i in range(1, n):
            nums[i] += nums[i - 1]
        
        return max(1, 1 - min(nums))