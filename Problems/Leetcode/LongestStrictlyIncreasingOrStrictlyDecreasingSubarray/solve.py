from typing import List

class Solution:
    def longestMonotonicSubarray(self, nums: List[int]) -> int:
        n = len(nums)
        inc_prefix = [1] * n
        dec_prefix = [1] * n
        for i in range(1, n):
            if nums[i] > nums[i - 1]:
                inc_prefix[i] = inc_prefix[i - 1] + 1
            if nums[i] < nums[i - 1]:
                dec_prefix[i] = dec_prefix[i - 1] + 1
        return max(max(inc_prefix), max(dec_prefix))