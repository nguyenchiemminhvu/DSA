from typing import List

class Solution:
    def dominantIndices(self, nums: List[int]) -> int:
        n = len(nums)
        res = 0
        sum_right = nums[-1]
        for i in range(n - 2, -1, -1):
            if nums[i] > sum_right / (n - i - 1):
                res += 1
            sum_right += nums[i]
        return res