from typing import List

class Solution:
    def numberOfSubarrays(self, nums: List[int], k: int) -> int:
        n = len(nums)
        odd_idx = []
        for i in range(n):
            if nums[i] & 1:
                odd_idx.append(i)
        
        no = len(odd_idx)
        if no < k:
            return 0
        
        res = 0
        for io in range(k - 1, no):
            l, r = odd_idx[io - k + 1], odd_idx[io]
            count_left, count_right = 1, 1
            while l - 1 >= 0 and nums[l - 1] % 2 == 0:
                l -= 1
                count_left += 1
            while r + 1 < n and nums[r + 1] % 2 == 0:
                r += 1
                count_right += 1
            res += count_left * count_right
        return res