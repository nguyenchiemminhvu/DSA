from typing import List

class Solution:
    def minSubarray(self, nums: List[int], p: int) -> int:
        total = sum(nums)
        total_mod = total % p
        if total_mod == 0:
            return 0
        
        n = len(nums)
        res = float('inf')
        prefix = 0
        m = {}
        m[0] = -1
        for i, val in enumerate(nums):
            prefix = (prefix + val) % p
            target_mod = (prefix - total_mod) % p
            if target_mod in m:
                res = min(res, i - m[target_mod])
            m[prefix] = i
        return -1 if res >= n else res