from typing import List

class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        mi = min(nums)
        if mi < k:
            return -1
        return len(set(nums)) - 1 + int(mi > k)