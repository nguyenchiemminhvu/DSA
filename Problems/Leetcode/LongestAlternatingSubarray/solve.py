from typing import List

class Solution:
    def alternatingSubarray(self, nums: List[int]) -> int:
        n = len(nums)
        def check(start: int, sign: int) -> int:
            count = 1
            for i in range(start + 1, n):
                if nums[i] - nums[i - 1] == sign:
                    count += 1
                else:
                    break
                sign *= -1
            return count
        
        res = 0
        for i in range(n):
            res = max(res, check(i, 1))
        return -1 if res < 2 else res