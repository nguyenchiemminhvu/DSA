from typing import List

class Solution:
    def minimumSumSubarray(self, nums: List[int], l: int, r: int) -> int:
        n = len(nums)
        for i in range(1, n):
            nums[i] += nums[i - 1]
        nums = [0] + nums
        res = float('inf')
        for sub in range(l, r+1):
            for i in range(sub + 1, n + 2):
                print(i - sub, i, nums[i - 1] - nums[i - sub - 1])
                val = nums[i - 1] - nums[i - sub - 1]
                if val > 0:
                    res = min(res, val)

        return -1 if res == float('inf') else res