from typing import List

class Solution:
    def findIndices(self, nums: List[int], i_diff: int, val_diff: int) -> List[int]:
        n = len(nums)
        for i in range(n):
            for j in range(i + i_diff, n):
                diff = abs(nums[i] - nums[j])
                if diff >= val_diff:
                    return [i, j]
        return [-1, -1]