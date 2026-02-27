from typing import List

class Solution:
    def smallestDivisor(self, nums: List[int], threshold: int) -> int:
        n = len(nums)

        def check_possible(div:int) -> bool:
            s = 0
            for val in nums:
                s += ((val + div - 1) // div)
            return s <= threshold

        left = 1
        right = max(nums)
        res = right
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                res = mid
                right = mid - 1
            else:
                left = mid + 1
        return res