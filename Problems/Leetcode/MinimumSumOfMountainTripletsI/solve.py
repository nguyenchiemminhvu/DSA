from typing import List

class Solution:
    def minimumSum(self, nums: List[int]) -> int:
        n = len(nums)
        min_left = [nums[0]] * n
        for i in range(1, n):
            min_left[i] = min(min_left[i - 1], nums[i])
        min_right = [nums[-1]] * n
        for i in range(n - 2, -1, -1):
            min_right[i] = min(min_right[i + 1], nums[i])
        
        res = float('inf')
        for i in range(1, n - 1):
            if min_left[i - 1] < nums[i] > min_right[i + 1]:
                res = min(res, min_left[i - 1] + nums[i] + min_right[i + 1])
        return -1 if res == float('inf') else res