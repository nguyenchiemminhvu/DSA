from typing import List

class Solution:
    def findNonMinOrMax(self, nums: List[int]) -> int:
        mi = min(nums)
        ma = max(nums)
        for val in nums:
            if val in [mi, ma]:
                continue
            return val
        return -1