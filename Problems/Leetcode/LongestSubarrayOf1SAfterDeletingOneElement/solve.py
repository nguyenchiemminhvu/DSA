from typing import List

class Solution:
    def longestSubarray(self, nums: List[int]) -> int:
        n = len(nums)
        k = 1
        res = 0
        count = [0] * 2
        left = 0
        for right in range(n):
            count[nums[right]] += 1
            while count[0] > k:
                count[nums[left]] -= 1
                left += 1
            res = max(res, right - left)
        return res