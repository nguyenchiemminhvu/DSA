from typing import List

class Solution:
    def threeSumClosest(self, nums: List[int], target: int) -> int:
        n = len(nums)
        nums.sort()

        dist = 0xFFFFFFFF
        res = 0xFFFFFFFF
        for i in range(n - 2):
            l = i + 1
            r = n - 1
            while l < r:
                s = nums[i] + nums[l] + nums[r]
                if s == target:
                    return s
                if abs(s - target) < dist:
                    res = s
                    dist = abs(s - target)
                if s > target:
                    r -= 1
                else:
                    l += 1
        return res