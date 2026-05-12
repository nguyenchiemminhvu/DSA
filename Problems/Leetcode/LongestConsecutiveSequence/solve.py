from typing import List

class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        res = 0
        s = set(nums)
        for val in s:
            if val - 1 not in s:
                # val is start of sequence
                cur = 1
                while val + 1 in s:
                    val += 1
                    cur += 1
                res = max(res, cur)
        return res
