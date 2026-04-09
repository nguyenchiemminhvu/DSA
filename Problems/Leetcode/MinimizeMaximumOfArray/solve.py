from typing import List

class Solution:
    def minimizeArrayValue(self, nums: List[int]) -> int:
        n = len(nums)

        def check_possible(upper: int) -> bool:
            carry = 0
            for i in range(n - 1, -1, -1):
                cur = nums[i] + carry
                if cur > upper:
                    carry = cur - upper
                else:
                    carry = 0
            return carry == 0

        left = nums[0]
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