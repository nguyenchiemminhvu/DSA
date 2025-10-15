from typing import List

class Solution:
    def minOperations(self, nums: List[int]) -> int:
        res = 0
        prev = nums[0]
        for i in range(1, len(nums)):
            if nums[i] <= prev:
                res += prev + 1 - nums[i]
                nums[i] = prev + 1
            prev = nums[i]
        return res