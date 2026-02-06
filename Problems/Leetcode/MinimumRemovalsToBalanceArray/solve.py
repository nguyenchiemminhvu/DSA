from typing import List

class Solution:
    def minRemoval(self, nums: List[int], k: int) -> int:
        n = len(nums)
        nums.sort()
        res = n - 1
        l = 0
        for r in range(1, n):
            while nums[l] * k < nums[r]:
                l += 1
            res = min(res, n - (r - l + 1))
        return res