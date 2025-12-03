from typing import List

class Solution:
    def maxSubsequence(self, nums: List[int], k: int) -> List[int]:
        nums = [(val, i) for i, val in enumerate(nums)]
        nums.sort(key=lambda x: x[0])
        n = len(nums)
        res = []
        r = n - 1
        while k:
            res.append(nums[r])
            r -= 1
            k -= 1
        return [x[0] for x in sorted(res, key=lambda p: p[1])]