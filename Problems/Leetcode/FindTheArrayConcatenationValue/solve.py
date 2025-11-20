from typing import List

class Solution:
    def findTheArrayConcVal(self, nums: List[int]) -> int:
        n = len(nums)
        l, r = 0, n - 1
        res = 0
        while l <= r:
            val = 0
            if l < r:
                val = int(str(nums[l]) + str(nums[r]))
            else:
                val = int(str(nums[l]))
            res += val
            l += 1
            r -= 1
        return res