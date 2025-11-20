from typing import List

class Solution:
    def sumOfGoodNumbers(self, nums: List[int], k: int) -> int:
        s = 0
        n = len(nums)
        for i, val in enumerate(nums):
            check = True
            if i - k >= 0 and val <= nums[i - k]:
                check = False
            if i + k < n and val <= nums[i + k]:
                check = False
            if check:
                s += val
        return s