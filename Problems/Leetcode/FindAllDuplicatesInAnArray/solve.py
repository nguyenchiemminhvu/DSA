from typing import List

class Solution:
    def findDuplicates(self, nums: List[int]) -> List[int]:
        n = len(nums)
        temp = [0] * (n + 1)
        for val in nums:
            temp[val] += n
        
        res = []
        for i, val in enumerate(temp):
            if val > n:
                res.append(i)
        return res