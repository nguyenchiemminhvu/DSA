from typing import List

class Solution:
    def constructTransformedArray(self, nums: List[int]) -> List[int]:
        n = len(nums)
        return [nums[((i + nums[i]) + n) % n] for i in range(n)]