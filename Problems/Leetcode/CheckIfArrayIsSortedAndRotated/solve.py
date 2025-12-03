from typing import List

class Solution:
    def check(self, nums: List[int]) -> bool:
        n = len(nums)
        pivot = n

        for i in range(1, n):
            if nums[i] < nums[i - 1]:
                pivot = i
                break
        
        nums.extend(nums[0:pivot])
        for i in range(pivot + 1, len(nums)):
            if nums[i] < nums[i - 1]:
                return False
        return True