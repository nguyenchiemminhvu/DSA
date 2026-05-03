from typing import List

class Solution:
    def maxOperations(self, nums: List[int], k: int) -> int:
        nums.sort()
        n = len(nums)
        left, right = 0, n - 1
        op = 0
        while left < right:
            s = nums[left] + nums[right]
            if s == k:
                op += 1
                left += 1
                right -= 1
            elif s > k:
                right -= 1
            else:
                left += 1
        
        return op