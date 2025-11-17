from typing import List

class Solution:
    def applyOperations(self, nums: List[int]) -> List[int]:
        n = len(nums)
        for i in range(1, n):
            if nums[i-1] == nums[i]:
                nums[i-1] *= 2
                nums[i] = 0
        c0 = 0
        i = 0
        for val in nums:
            if val == 0:
                c0 += 1
            else:
                nums[i] = val
                i += 1
        while c0:
            c0 -= 1
            nums[i] = 0
            i += 1
        return nums