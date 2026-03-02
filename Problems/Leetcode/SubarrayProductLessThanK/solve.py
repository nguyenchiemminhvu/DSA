from typing import List

class Solution:
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        if k == 0 or k == 1:
            return 0
        
        res = 0
        n = len(nums)
        left = 0
        cur_prod = 1
        for right in range(n):
            cur_prod *= nums[right]
            while cur_prod >= k:
                cur_prod //= nums[left]
                left += 1
            res += (right - left + 1)
        return res