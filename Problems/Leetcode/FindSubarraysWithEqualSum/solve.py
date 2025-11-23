from typing import List

class Solution:
    def findSubarrays(self, nums: List[int]) -> bool:
        f = {}
        for i in range(1, len(nums)):
            val = nums[i - 1] + nums[i]
            f[val] = f.get(val, 0) + 1
        
        return any(v >= 2 for v in f.values())