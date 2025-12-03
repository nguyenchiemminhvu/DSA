from typing import List

class Solution:
    def distinctAverages(self, nums: List[int]) -> int:
        nums.sort()
        l, r = 0, len(nums) - 1
        s = set()
        while l < r:
            s.add((nums[l] + nums[r]) / 2)
            l += 1
            r -= 1
        return len(s)