from typing import List

class Solution:
    def maximumDifference(self, nums: List[int]) -> int:
        res = -1
        cur_max = -1
        while nums:
            val = nums.pop()
            if val < cur_max:
                res = max(res, cur_max - val)
            cur_max = max(cur_max, val)
        return res