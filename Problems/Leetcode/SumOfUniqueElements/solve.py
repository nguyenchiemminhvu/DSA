from typing import List

class Solution:
    def sumOfUnique(self, nums: List[int]) -> int:
        s = 0
        f = {}
        for val in nums:
            f[val] = f.get(val, 0) + 1
        for val in nums:
            if f[val] == 1:
                s += val
        return s