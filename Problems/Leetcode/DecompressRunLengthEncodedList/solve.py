from typing import List

class Solution:
    def decompressRLElist(self, nums: List[int]) -> List[int]:
        n = len(nums)
        res = []
        for i in range(0, n, 2):
            res.extend([nums[i + 1]] * nums[i])
        return res