from typing import List

class Solution:
    def minPairSum(self, nums: List[int]) -> int:
        nums.sort()
        left = 0
        right = len(nums) - 1
        res = 0
        while left < right:
            res = max(res, nums[left] + nums[right])
            left += 1
            right -= 1
        return res