from typing import List
from collections import Counter

class Solution:
    def minimumOperations(self, nums: List[int]) -> int:
        f = Counter(nums) 
        op = 0
        i = 0
        n = len(nums)
        while any(v >= 2 for k, v in f.items()):
            for offset in range(3):
                if i + offset < n:
                    f[nums[i + offset]] -= 1
            i += 3
            op += 1
        return op