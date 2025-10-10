from typing import List

class Solution:
    def splitArray(self, nums: List[int], k: int) -> int:
        def can_split(nums:List[int], k:int, threshold:int) -> bool:
            count_segment = 1
            cur_sum = 0
            for val in nums:
                if cur_sum + val <= threshold:
                    cur_sum += val
                else:
                    cur_sum = val
                    count_segment += 1
                    if count_segment > k:
                        return False
            return True
        
        min_largest = 0xFFFFFFFF
        left = max(nums)
        right = sum(nums)
        while left <= right:
            # Can we split nums into ≤ k subarrays such that each subarray sum ≤ mid?
            mid = left + (right - left) // 2
            if can_split(nums, k, mid):
                right = mid - 1
                min_largest = min(min_largest, mid)
            else:
                left = mid + 1
        return min_largest