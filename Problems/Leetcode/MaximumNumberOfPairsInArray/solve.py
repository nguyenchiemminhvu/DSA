from typing import List
from collections import Counter

class Solution:
    def numberOfPairs(self, nums: List[int]) -> List[int]:
        f = Counter(nums)
        count = 0
        for k, v in f.items():
            count += v // 2
        return [count, len(nums) - count * 2]