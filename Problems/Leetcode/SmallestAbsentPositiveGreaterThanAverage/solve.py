from typing import List

class Solution:
    def smallestAbsent(self, nums: List[int]) -> int:
        avg = max(0, sum(nums) // len(nums))
        s = set(nums)
        n = len(nums)
        for val in range(avg + 1, 1001):
            if val not in s:
                return val
        return 0