from typing import List

class Solution:
    def findMaxK(self, nums: List[int]) -> int:
        nums.sort()
        s = set(nums)
        for val in nums:
            if val >= 0:
                break
            if -val in s:
                return -val
        return -1