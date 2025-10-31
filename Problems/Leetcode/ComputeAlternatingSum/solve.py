from typing import List

class Solution:
    def alternatingSum(self, nums: List[int]) -> int:
        res = 0
        sign = 1
        for val in nums:
            res += (val * sign)
            sign *= -1
        return res