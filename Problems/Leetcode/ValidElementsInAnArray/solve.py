from typing import List

class Solution:
    def findValidElements(self, nums: list[int]) -> list[int]:
        n = len(nums)
        left = nums[:]
        right = nums[:]
        for i in range(1, n):
            left[i] = max(left[i - 1], nums[i])
        for i in range(n - 2, -1, -1):
            right[i] = max(right[i + 1], nums[i])
        
        res = []
        for i in range(n):
            check_left = check_right = True
            if i > 0:
                check_left = nums[i] > left[i - 1]
            if i < n - 1:
                check_right = nums[i] > right[i + 1]
            if check_left or check_right:
                res.append(nums[i])
        return res