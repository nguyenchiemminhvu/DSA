# https://leetcode.com/problems/largest-divisible-subset

from typing import List
from collections import deque

class Solution:
    def largestDivisibleSubset(self, nums: List[int]) -> List[int]:
        nums.sort()
        n = len(nums)

        dp = [1] * n
        for i in range(1, n):
            for j in range(0, i):
                if (nums[i] % nums[j] == 0):
                    dp[i] = max(dp[i], dp[j] + 1)
        
        max_dp = 1
        max_idx = -1
        for i in range(0, n):
            if (dp[i] >= max_dp):
                max_dp = dp[i]
                max_idx = i
        
        res = deque([nums[max_idx]])
        for i in range(max_idx - 1, -1, -1):
            if (dp[i] == max_dp - 1 and nums[max_idx] % nums[i] == 0):
                res.appendleft(nums[i])
                max_dp -= 1
                max_idx = i
        
        return list(res)

if __name__ == "__main__":
    nums = [1, 2, 3]
    sol = Solution()
    print(sol.largestDivisibleSubset(nums))  # Output: [1, 2] or [1, 3]