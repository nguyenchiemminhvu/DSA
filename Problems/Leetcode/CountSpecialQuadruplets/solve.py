from typing import List

class Solution:
    def countQuadruplets(self, nums: List[int]) -> int:
        n = len(nums)
        f = {}
        count = 0
        for i in range(n):
            for j in range(i + 1, n):
                for k in range(j + 1, n):
                    val = nums[k] - nums[i] - nums[j]
                    if val in f:
                        count += f[val]
            f[nums[i]] = f.get(nums[i], 0) + 1
        return count