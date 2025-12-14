from typing import List

class Solution:
    def absDifference(self, nums: List[int], k: int) -> int:
        nums.sort()
        return abs(sum(nums[len(nums) - k:]) - sum(nums[:k]))