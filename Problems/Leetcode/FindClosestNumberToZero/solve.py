from typing import List

class Solution:
    def findClosestNumber(self, arr: List[int]) -> int:
        dist = float('inf')
        res = float('inf')
        for val in arr:
            if dist > abs(val):
                dist = abs(val)
                res = val
            elif dist == abs(val):
                res = max(res, val)
        return res