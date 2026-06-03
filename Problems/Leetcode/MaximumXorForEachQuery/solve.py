from typing import List

class Solution:
    def getMaximumXor(self, nums: List[int], max_bit: int) -> List[int]:
        n = len(nums)
        
        res = []
        x = 0
        for i in range(n):
            mask = (1 << max_bit) - 1
            x ^= nums[i]
            res.append(x ^ mask)
        res.reverse()
        return res