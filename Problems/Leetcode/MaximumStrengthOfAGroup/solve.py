from typing import List

class Solution:
    def maxStrength(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 1:
            return nums[0]
        res = float('-inf')
        for mask in range(1, 1 << n):
            p = 1
            for i in range(n):
                if (1 << i) & mask:
                    p *= nums[i]
            res = max(res, p)
        return res