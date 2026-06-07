from typing import List

class Solution:
    def longestSubarray(self, nums: List[int]) -> int:
        n = len(nums)

        res = 2
        cur = 2
        for i in range(2, n):
            if nums[i] == nums[i - 2] + nums[i - 1]:
                cur += 1
            else:
                cur = 2
            res = max(res, cur)
        return res