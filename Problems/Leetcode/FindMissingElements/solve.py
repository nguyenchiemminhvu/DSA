from typing import List

class Solution:
    def findMissingElements(self, nums: List[int]) -> List[int]:
        left = min(nums)
        right = max(nums)
        s = set(nums)
        res = []
        for val in range(left, right):
            if val not in s:
                res.append(val)
        return res