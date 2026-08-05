from typing import List

class Solution:
    def minElements(self, nums: List[int], limit: int, goal: int) -> int:
        s = sum(nums)
        diff = abs(goal - s)
        return (diff + (limit - 1)) // limit