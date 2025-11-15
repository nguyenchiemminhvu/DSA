from typing import List

class Solution:
    def sumCounts(self, nums: List[int]) -> int:
        res = 0
        n = len(nums)
        for sublen in range(0, n):
            for i in range(0, n - sublen):
                s = set()
                for j in range(i, i + sublen + 1):
                    s.add(nums[j])
                res += len(s) ** 2
        return res