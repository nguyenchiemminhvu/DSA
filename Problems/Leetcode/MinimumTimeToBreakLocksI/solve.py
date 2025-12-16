from typing import List
from itertools import permutations

class Solution:
    def findMinimumTime(self, nums: List[int], k: int) -> int:
        n = len(nums)
        res = float('inf')
        perms = permutations(nums)
        for arr in perms:
            times = 0
            x = 1
            for val in arr:
                times += val // x
                if val % x > 0:
                    times += 1
                x += k
            res = min(res, times)
        
        return res