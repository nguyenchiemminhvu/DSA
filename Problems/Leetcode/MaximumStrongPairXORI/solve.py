from typing import List

class Solution:
    def maximumStrongPairXor(self, nums: List[int]) -> int:
        def upper_bound(arr: List[int], target:int, start:int = 0) -> int:
            left = start
            right = len(arr) - 1
            found = right + 1
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] > target:
                    found = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return found
        
        n = len(nums)
        nums.sort()
        res = 0
        for i in range(0, n):
            upper = upper_bound(nums, nums[i] * 2, i + 1)
            for j in range(i + 1, upper):
                res = max(res, nums[i] ^ nums[j])
        return res