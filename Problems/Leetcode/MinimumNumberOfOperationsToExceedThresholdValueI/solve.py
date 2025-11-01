from typing import List

class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        def lower_bound(arr: List[int], target: int) -> int:
            n = len(arr)
            left, right, found = 0, n - 1, n
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] >= target:
                    found = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return found

        nums.sort()
        return lower_bound(nums, k)