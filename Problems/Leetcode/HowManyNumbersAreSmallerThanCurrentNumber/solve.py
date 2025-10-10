from typing import List

class Solution:
    def smallerNumbersThanCurrent(self, nums: List[int]) -> List[int]:
        def lower_bound(arr: List[int], target:int) -> int:
            left = 0
            right = len(arr) - 1
            found_idx = right + 1
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] >= target:
                    found_idx = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return found_idx
        
        s = sorted(nums)
        for i in range(len(nums)):
            lower = lower_bound(s, nums[i])
            nums[i] = lower
        return nums