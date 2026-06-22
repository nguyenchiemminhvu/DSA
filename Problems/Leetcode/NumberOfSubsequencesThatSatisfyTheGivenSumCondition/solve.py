from typing import List

class Solution:
    def numSubseq(self, nums: List[int], target: int) -> int:
        mod = 10**9 + 7

        nums.sort()
        n = len(nums)

        res = 0
        left, right = 0, n - 1
        while left <= right:
            if nums[left] + nums[right] <= target:
                res = (res + pow(2, (right - left), mod)) % mod
                left += 1
            else:
                right -= 1
        
        return res