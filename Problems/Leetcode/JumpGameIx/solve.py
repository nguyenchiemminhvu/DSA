from typing import List

class Solution:
    def maxValue(self, nums: List[int]) -> List[int]:
        res = nums[:]

        n = len(nums)
        left_max = [0] * n
        right_min = [0] * n

        left_max[0] = nums[0]
        for i in range(1, n):
            left_max[i] = max(left_max[i - 1], nums[i])
        
        right_min[n - 1] = nums[-1]
        for i in range(n - 2, -1, -1):
            right_min[i] = min(right_min[i + 1], nums[i])
        
        pivot_idx = 0
        pivot_max = nums[0]
        for i in range(n):
            pivot_max = max(pivot_max, nums[i])

            if i == n - 1 or left_max[i] <= right_min[i + 1]:
                for j in range(pivot_idx, i + 1):
                    res[j] = pivot_max
                if i < n - 1:
                    pivot_idx = i + 1
                    pivot_max = nums[pivot_idx]

        return res