from collections import Counter
from typing import List

class Solution:
    def isPossibleToSplit(self, nums: List[int]) -> bool:
        f = Counter(nums)
        for k, v in f.items():
            if v > 2:
                return False
        return True