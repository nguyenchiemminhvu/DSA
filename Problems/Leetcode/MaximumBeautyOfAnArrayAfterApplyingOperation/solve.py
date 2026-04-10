from typing import List

class Solution:
    def maximumBeauty(self, nums: List[int], k: int) -> int:
        nums.sort()

        n = len(nums)
        res = 0
        left = 0
        for right in range(n):
            while nums[right] - nums[left] > 2 * k:
                left += 1
            res = max(res, right - left + 1)
        return res