from typing import List
from collections import defaultdict

class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        n = len(nums)
        it = 0
        s = defaultdict(int)
        for i, val in enumerate(nums):
            if s[val] > 1:
                continue
            nums[it] = nums[i]
            it += 1
            s[val] += 1
        return it