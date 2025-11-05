from typing import List

class Solution:
    def smallestRangeI(self, nums: List[int], k: int) -> int:
        nums.sort()
        nums[0] += k
        nums[-1] -= k
        return max(0, nums[-1] - nums[0])