from typing import List

class Solution:
    def maximizeSum(self, nums: List[int], k: int) -> int:
        a = max(nums)
        b = a + k - 1
        return (b - a + 1) * (a + b) // 2