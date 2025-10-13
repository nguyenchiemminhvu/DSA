from typing import List

class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        count = 0
        mask = (1 << k) - 1
        while len(nums) > 0:
            bit = (1 << (nums.pop() - 1))
            mask &= ~bit
            count += 1
            if not mask:
                break
        return count