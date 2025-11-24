from typing import List

class Solution:
    def maxAscendingSum(self, nums: List[int]) -> int:
        prefix = [val for val in nums]
        for i in range(1, len(nums)):
            if nums[i] > nums[i - 1]:
                prefix[i] += prefix[i - 1]
        
        return max(prefix)