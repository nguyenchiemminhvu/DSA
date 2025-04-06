# https://leetcode.com/problems/largest-divisible-subset

from typing import List

class Solution:
    def largestDivisibleSubset(self, nums: List[int]) -> List[int]:
        nums.sort()
        n = len(nums)

        dp = [1] * n
        prev = [-1] * n
        max_idx = 0
        for i in range(1, n):
            for j in range(0, i):
                if (nums[i] % nums[j] == 0):
                    dp[i] = max(dp[i], dp[j] + 1)
                    prev[i] = j
            if (dp[i] > dp[max_idx]):
                max_idx = i
        
        result = []
        while (max_idx != -1):
            result.append(nums[max_idx])
            max_idx = prev[max_idx]        
        return result

if __name__ == "__main__":
    nums = [1, 2, 3]
    sol = Solution()
    print(sol.largestDivisibleSubset(nums))  # Output: [1, 2] or [1, 3]