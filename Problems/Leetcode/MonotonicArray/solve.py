from typing import List

class Solution:
    def isMonotonic(self, nums: List[int]) -> bool:
        n = len(nums)
        if n == 1:
            return True
        
        sign = (nums[-1] - nums[0]) >= 0
        for i in range(1, n):
            if nums[i] != nums[i - 1] and sign != ((nums[i] - nums[i - 1]) >= 0):
                return False
        return True