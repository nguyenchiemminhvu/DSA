from typing import List
from collections import Counter

class Solution:
    def firstUniqueEven(self, nums: list[int]) -> int:
        f = Counter(nums)
        for val in nums:
            if val % 2 == 0 and f[val] == 1:
                return val
        return -1