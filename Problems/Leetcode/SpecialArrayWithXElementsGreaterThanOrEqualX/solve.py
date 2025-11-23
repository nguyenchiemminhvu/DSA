from typing import List
from collections import Counter

class Solution:
    def specialArray(self, nums: List[int]) -> int:
        def lower_bound(arr: List[int], target: int) -> int:
            left, right, found = 0, len(arr) - 1, len(arr)
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] >= target:
                    found = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return found
        
        f = Counter(nums)
        keys = sorted(f.keys())
        
        for val in range(len(nums) + 1):
            lower = lower_bound(keys, val)
            count = 0
            for i in range(lower, len(keys)):
                count += f[keys[i]]
            if count == val:
                return val

        return -1