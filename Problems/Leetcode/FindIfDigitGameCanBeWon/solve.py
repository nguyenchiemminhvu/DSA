from typing import List

class Solution:
    def canAliceWin(self, nums: List[int]) -> bool:
        a, b = 0, 0
        for val in nums:
            if val < 10:
                a += val
            else:
                b += val
        return a != b