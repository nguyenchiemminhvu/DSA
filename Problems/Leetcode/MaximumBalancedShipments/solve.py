from typing import List

class Solution:
    def maxBalancedShipments(self, nums: List[int]) -> int:
        n = len(nums)
        count = 0
        prev = -1
        i = 0
        while i < n:
            if prev == -1:
                prev = nums[i]
                continue
            else:
                if nums[i] < prev:
                    count += 1
                    prev = -1
                else:
                    prev = nums[i]
            i += 1
        return count