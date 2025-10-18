from typing import List

class Solution:
    def findUnsortedSubarray(self, nums: List[int]) -> int:
        temp = sorted([val for val in nums])
        l = len(nums)
        r = -1
        for i in range(0, len(nums)):
            if nums[i] != temp[i]:
                l = i
                break
        for i in range(len(nums) - 1, -1, -1):
            if nums[i] != temp[i]:
                r = i
                break
        return 0 if l > r else r - l + 1