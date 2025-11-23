from typing import List

class Solution:
    def minimumCost(self, nums: List[int]) -> int:
        return nums[0] + sum(sorted(nums[1:])[0:2])