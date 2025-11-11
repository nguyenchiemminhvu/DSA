from typing import List

class Solution:
    def maxFrequencyElements(self, nums: List[int]) -> int:
        f = {}
        for val in nums:
            f[val] = f.get(val, 0) + 1
        pivot = max(f.values())
        count = 0
        for val in nums:
            if f[val] == pivot:
                count += 1
        return count