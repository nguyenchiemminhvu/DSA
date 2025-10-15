from typing import List

class Solution:
    def largestSumAfterKNegations(self, nums: List[int], k: int) -> int:
        def upper_bound(arr: List[int], target) -> int:
            n = len(arr)
            left, right, found = 0, n - 1, n
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] > target:
                    found = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return found

        nums.sort()
        non_neg_idx = upper_bound(nums, -1)
        for i in range(0, non_neg_idx):
            if k > 0 and i < len(nums):
                nums[i] *= -1
                k -= 1
        s = sum(nums)
        if k & 1:
            s -= (min(nums) * 2)

        return s