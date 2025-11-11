from typing import List

class Solution:
    def returnToBoundaryCount(self, nums: List[int]) -> int:
        n = len(nums)
        pivot = 0
        count = 0
        for val in nums:
            pivot += val
            if pivot == 0:
                count += 1
        return count