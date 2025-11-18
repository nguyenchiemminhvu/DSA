from typing import List

class Solution:
    def minBitwiseArray(self, nums: List[int]) -> List[int]:
        n = len(nums)
        res = [-1] * n
        for i in range(n):
            for val in range(0, nums[i]):
                if (val | val + 1) == nums[i]:
                    res[i] = val
                    break
        return res