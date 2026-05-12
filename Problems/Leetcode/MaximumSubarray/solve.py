from typing import List

class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        # kadane algorithm
        # max_so_far = nums[0]
        # max_cur = 0
        # for val in nums:
        #     max_cur = max(val, max_cur + val)
        #     max_so_far = max(max_so_far, max_cur)
        # return max_so_far

        res = float('-inf')
        cur = 0
        for val in nums:
            cur += val
            if cur > res:
                res = cur
            if cur < 0:
                cur = 0
        return res