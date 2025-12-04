from typing import List

class Solution:
    def maxOperations(self, nums: List[int]) -> int:
        nums.reverse()
        count = 0
        ref = nums[-1] + nums[-2]
        while len(nums) >= 2:
            a, b = nums[-1], nums[-2]
            if a + b != ref:
                break
            count += 1
            nums.pop()
            nums.pop()
        return count