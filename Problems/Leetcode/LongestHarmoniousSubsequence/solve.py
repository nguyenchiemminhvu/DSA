from typing import List

class Solution:
    def findLHS(self, nums: List[int]) -> int:
        n = len(nums)
        freq = {}
        for val in nums:
            freq[val] = freq.get(val, 0) + 1
        
        res = 0
        for k, f in freq.items():
            if k - 1 in freq:
                res = max(res, freq[k - 1] + freq[k])
            if k + 1 in freq:
                res = max(res, freq[k] + freq[k + 1])
        return res