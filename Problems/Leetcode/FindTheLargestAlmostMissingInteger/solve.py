from typing import List
from collections import Counter

class Solution:
    def largestInteger(self, nums: List[int], k: int) -> int:
        n = len(nums)
        counter = Counter(nums)
        if k == 1:
            return max([-1] + [k for k, v in counter.items() if v <= 1])
        if k == n:
            return max(nums)
        return max([-1] + [val for val in [nums[0], nums[-1]] if counter[val] <= 1])
        