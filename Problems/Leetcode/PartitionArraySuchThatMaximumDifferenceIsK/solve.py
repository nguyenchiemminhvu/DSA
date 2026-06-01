from typing import List

class Solution:
    def partitionArray(self, nums: List[int], k: int) -> int:
        nums = sorted(list(set(nums)))
        n = len(nums)
        
        count = 1
        prev = nums[0]
        for i in range(1, n):
            if nums[i] - prev > k:
                count += 1
                prev = nums[i]
        return count