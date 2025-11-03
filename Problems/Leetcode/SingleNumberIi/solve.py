from typing import List

class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        f = {}
        for val in nums:
            f[val] = f.get(val, 0) + 1
        for val in nums:
            if f[val] == 1:
                return val
        return -1