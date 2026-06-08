from collections import defaultdict
from typing import List

class Solution:
    def tupleSameProduct(self, nums: List[int]) -> int:
        n = len(nums)
        mp = defaultdict(int)
        for i in range(n):
            for j in range(i + 1, n):
                mp[nums[i] * nums[j]] += 1
        
        res = 0
        for k, v in mp.items():
            res += (v * (v - 1) // 2) * 8

        return res