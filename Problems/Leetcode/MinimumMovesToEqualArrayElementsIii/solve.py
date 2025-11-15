from typing import List

class Solution:
    def minMoves(self, nums: List[int]) -> int:
        top = max(nums)
        res = 0
        for val in nums:
            res += top - val
        return res