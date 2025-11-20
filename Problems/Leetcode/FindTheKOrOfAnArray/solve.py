from typing import List
from collections import defaultdict

class Solution:
    def findKOr(self, nums: List[int], k: int) -> int:
        f = defaultdict(int)
        for val in nums:
            for i in range(32):
                if val & (1 << i):
                    f[i] += 1
        
        res = 0
        for i in range(32):
            if f[i] >= k:
                res |= (1 << i)
        return res