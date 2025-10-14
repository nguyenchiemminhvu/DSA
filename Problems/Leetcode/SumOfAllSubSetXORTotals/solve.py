from typing import List

class Solution:
    def subsetXORSum(self, nums: List[int]) -> int:
        n = len(nums)
        nn = (1 << n)
        res = 0
        for mask in range(1, nn):
            x = 0
            for i in range(0, n):
                if (1 << i) & mask:
                    x ^= nums[i]
            res += x
        return res