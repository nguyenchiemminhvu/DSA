from typing import List

class Solution:
    def sortPermutation(self, nums: List[int]) -> int:
        res = 0xFFFFFFFFFFFFFFFF
        for i in range(len(nums)):
            if nums[i] != i:
                res &= nums[i]
        return 0 if res == 0xFFFFFFFFFFFFFFFF else res