from typing import List

class Solution:
    def findLengthOfLCIS(self, nums: List[int]) -> int:
        n = len(nums)
        prefix = [1] * n
        for i in range(1, n):
            if nums[i] > nums[i - 1]:
                prefix[i] = prefix[i - 1] + 1
        
        return max(prefix)