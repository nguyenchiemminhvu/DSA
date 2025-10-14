from typing import List

class Solution:
    def hasIncreasingSubarrays(self, nums: List[int], k: int) -> bool:
        n = len(nums)
        dp = [1] * n
        for i in range(1, n):
            if nums[i] > nums[i - 1]:
                dp[i] = dp[i-1] + 1
        
        for i in range(k,n):
            if (dp[i] >= 2 * k) or (dp[i] >= k and dp[i - k] >= k):
                return True
        return False