from typing import List

class Solution:
    def minimumDistance(self, nums: List[int]) -> int:
        m = {}
        for i, val in enumerate(nums):
            if val not in m:
                m[val] = []
            m[val].append(i)
        
        res = float('inf')
        for k, v in m.items():
            if len(v) >= 3:
                for i in range(2, len(v)):
                    res = min(res, (v[i] - v[i - 2]) * 2)
        return -1 if res == float('inf') else res