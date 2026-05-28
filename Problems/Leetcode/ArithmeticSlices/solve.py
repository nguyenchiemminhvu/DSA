from typing import List

class Solution:
    def numberOfArithmeticSlices(self, nums: List[int]) -> int:
        n = len(nums)

        count = 0
        for i in range(n - 2):
            diff = nums[i + 1] - nums[i]
            for j in range(i + 2, n):
                if nums[j] - nums[j - 1] != diff:
                    break
                count += 1
        return count