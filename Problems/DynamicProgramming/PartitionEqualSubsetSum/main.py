# https://leetcode.com/problems/partition-equal-subset-sum/description

from collections import List

class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        s = sum(nums)
        if (s & 1):
            return False

        half_s = s // 2
        dp = [False] * (half_s + 1)
        dp[0] = True

        for num in nums:
            for i in range(half_s, num - 1, -1):
                dp[i] = dp[i] or dp[i - num]

        return dp[half_s]

if __name__ == "__main__":
    nums = [1, 5, 11, 5]
    solution = Solution()
    print(solution.canPartition(nums))  # Output: True
