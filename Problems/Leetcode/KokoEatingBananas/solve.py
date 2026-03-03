from typing import List

class Solution:
    def minEatingSpeed(self, nums: List[int], h: int) -> int:
        n = len(nums)

        def check_possible(k: int) -> bool:
            total_h = 0
            for val in nums:
                if val <= k:
                    total_h += 1
                else:
                    total_h += (val + k - 1) // k
            return total_h <= h

        left = 1
        right = sum(nums)
        k = right
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                k = mid
                right = mid - 1
            else:
                left = mid + 1
        return k