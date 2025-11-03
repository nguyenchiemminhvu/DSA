from typing import List

class Solution:
    def findMaxAverage(self, nums: List[int], k: int) -> float:
        s = 0
        for i in range(k):
            s += nums[i]
        res = s / k
        for i in range(k, len(nums)):
            s -= nums[i - k]
            s += nums[i]
            res = max(res, s / k)
        return res