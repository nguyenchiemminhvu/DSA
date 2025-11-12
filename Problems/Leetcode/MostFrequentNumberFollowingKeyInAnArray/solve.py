from collections import defaultdict
from typing import List

class Solution:
    def mostFrequent(self, nums: List[int], key: int) -> int:
        f = defaultdict(int)
        for i in range(1, len(nums)):
            if nums[i - 1] == key:
                f[nums[i]] += 1
        target_f = max(f.values())
        for k, v in f.items():
            if v == target_f:
                return k
        return -1