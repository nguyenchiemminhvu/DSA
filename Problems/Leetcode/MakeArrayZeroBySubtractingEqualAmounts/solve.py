from typing import List

class Solution:
    def minimumOperations(self, nums: List[int]) -> int:
        nums.sort()
        cur = 0
        res = 0
        for val in nums:
            if val > cur:
                res += 1
            cur = val
        return res