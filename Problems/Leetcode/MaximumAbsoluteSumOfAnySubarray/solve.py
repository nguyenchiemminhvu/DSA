from typing import List

class Solution:
    def maxAbsoluteSum(self, nums: List[int]) -> int:
        def kadane_max(arr: List[int]) -> int:
            res = arr[0]
            cur_max = arr[0]
            for i in range(1, len(arr)):
                val = arr[i]
                cur_max = max(val, cur_max + val)
                res = max(res, cur_max)
            return res
        
        def kadane_min(arr: List[int]) -> int:
            res = arr[0]
            cur_min = arr[0]
            for i in range(1, len(arr)):
                val = arr[i]
                cur_min = min(val, cur_min + val)
                res = min(res, cur_min)
            return res
        
        mx = kadane_max(nums)
        mi = kadane_min(nums)
        return max(abs(mi), abs(mx))