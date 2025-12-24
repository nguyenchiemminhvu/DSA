from typing import List

class Solution:
    def minOperations(self, nums: List[int]) -> int:
        n = len(nums)
        op = 0
        for i in range(0, n - 2):
            if nums[i] == 0:
                nums[i + 1] = (nums[i + 1] + 1) % 2
                nums[i + 2] = (nums[i + 2] + 1) % 2
                op += 1

        if nums[-2] == 0 or nums[-1] == 0:
            return -1
        return op