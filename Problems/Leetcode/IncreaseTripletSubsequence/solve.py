from collections import deque

class Solution:
    def increasingTriplet(self, nums: List[int]) -> bool:
        n = len(nums)
        val1 = 0xFFFFFFFF
        val2 = 0xFFFFFFFF
        for i, val in enumerate(nums):
            if val <= val1:
                val1 = val
            else: # val > val1
                if val <= val2:
                    val2 = val
                else:
                    return True
        return False