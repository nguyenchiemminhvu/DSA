from typing import List

class Solution:
    def subarraySum(self, nums: List[int]) -> int:
        n = len(nums)
        prefix = [0] * (n + 1)
        for i in range(0, n):
            prefix[i + 1] = prefix[i] + nums[i]
        
        res = 0
        for i in range(n):
            start = max(0, i - nums[i])
            res += prefix[i + 1] - prefix[start]
        return res