from typing import List

class Solution:
    def largestAltitude(self, gain: List[int]) -> int:
        res = 0
        cur = 0
        for g in gain:
            cur += g
            res = max(res, cur)
        return res