from typing import List

class Solution:
    def minimumOperations(self, nums: List[int]) -> int:
        return sum(min(val % 3, 3 - (val % 3)) for val in nums)