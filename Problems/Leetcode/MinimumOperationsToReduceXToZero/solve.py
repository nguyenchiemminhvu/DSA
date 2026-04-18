from typing import List

class Solution:
    def minOperations(self, nums: List[int], x: int) -> int:
        n = len(nums)
        s = sum(nums)
        if s < x:
            return -1
        
        s_sub = s - x

        # find longest subarray sum to s_sub
        longest = -1
        cur_s = 0
        left = 0
        for right in range(n):
            cur_s += nums[right]
            while cur_s > s_sub:
                cur_s -= nums[left]
                left += 1
            if cur_s == s_sub:
                longest = max(longest, right - left + 1)
        
        return -1 if longest == -1 else n - longest