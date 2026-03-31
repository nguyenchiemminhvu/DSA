from typing import List

class Solution:
    def minAbsoluteDifference(self, nums: list[int]) -> int:
        last_idx = {}
        res = float('inf')
        n = len(nums)
        for i in range(n):
            if nums[i] == 1:
                if 2 in last_idx:
                    res = min(res, i - last_idx[2])
            elif nums[i] == 2:
                if 1 in last_idx:
                    res = min(res, i - last_idx[1])
            last_idx[nums[i]] = i
        return -1 if res == float('inf') else res