from typing import List

class Solution:
    def minimumDeletions(self, nums: List[int]) -> int:
        n = len(nums)
        l = nums.index(min(nums))
        r = nums.index(max(nums))
        if l > r:
            l, r = r, l
        return min(
            (l + 1) + (n - r),
            r + 1,
            n - l
        )