from typing import List

class Solution:
    def maxAlternatingSum(self, nums: List[int]) -> int:
        add = 0
        sub = 0
        for val in nums:
            add = max(add, sub + val)
            sub = max(sub, add - val)
        return max(add, sub)