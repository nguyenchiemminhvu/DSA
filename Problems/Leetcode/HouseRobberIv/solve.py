from typing import List

class Solution:
    def minCapability(self, nums: List[int], k: int) -> int:
        n = len(nums)

        def check_possible(cap: int) -> bool:
            i = 0
            count = 0
            while i < n:
                if nums[i] <= cap:
                    count += 1
                    i += 2
                else:
                    i += 1
            return count >= k

        l, r = min(nums), max(nums)
        res = r
        while l <= r:
            m = l + (r - l) // 2
            if check_possible(m):
                res = m
                r = m - 1
            else:
                l = m + 1
        return res