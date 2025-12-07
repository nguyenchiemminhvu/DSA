from typing import List

class Solution:
    def maxSum(self, nums: List[int]) -> int:
        res = max(nums)
        s = set(val for val in nums if val >= 0)
        if len(s) > 0:
            res = max(res, sum(s))
        return res