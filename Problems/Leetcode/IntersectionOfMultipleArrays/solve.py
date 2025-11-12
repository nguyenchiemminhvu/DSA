from typing import List

class Solution:
    def intersection(self, nums: List[List[int]]) -> List[int]:
        s = set(nums[0])
        for row in nums:
            s &= set(row)
        return sorted(list(s))