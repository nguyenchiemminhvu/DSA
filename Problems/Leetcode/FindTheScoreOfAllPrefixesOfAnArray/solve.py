from typing import List

class Solution:
    def findPrefixScore(self, nums: List[int]) -> List[int]:
        cur_max = 0
        res = []
        for val in nums:
            cur_max = max(cur_max, val)
            res.append(cur_max + val)
        for i in range(1, len(res)):
            res[i] += res[i - 1]
        return res