from typing import List

class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        n = len(nums)
        mi, ma = min(nums), max(nums)
        if mi > 1:
            return 1
        
        s = set()
        for val in nums:
            s.add(val)
        
        for val in range(1, n + 2):
            if val not in s:
                return val
        return ma + 1