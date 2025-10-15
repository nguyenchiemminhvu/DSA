from typing import List

class Solution:
    def maxIncreasingSubarrays(self, nums: List[int]) -> int:
        n = len(nums)
        dp = [1] * n
        for i in range(1, n):
            if nums[i] > nums[i - 1]:
                dp[i] = dp[i-1] + 1
        
        def test_k_candidate(k:int) -> bool:
            for i in range(k,n):
                if (dp[i] >= 2 * k) or (dp[i] >= k and dp[i - k] >= k):
                    return True
            return False

        left = 1
        right = n // 2
        res = left
        while left <= right:
            mid = left + (right - left) // 2
            test_ok = test_k_candidate(mid)
            if test_ok:
                res = mid
                left = mid + 1
            else:
                right = mid - 1
        return res