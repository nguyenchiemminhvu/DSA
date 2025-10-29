from typing import List

class Solution:
    def maximumOr(self, nums: List[int], k: int) -> int:
        n = len(nums)
        prefix = [0] * (n + 1)
        suffix = [0] * (n + 1)
        for i in range(0, n):
            prefix[i + 1] = prefix[i] | nums[i]
        for i in range(n - 1, -1, -1):
            suffix[i] = suffix[i + 1] | nums[i]
        
        res = 0
        for i in range(0, n):
            others = prefix[i] | suffix[i + 1]
            res = max(res, others | (nums[i] << k))
        return res