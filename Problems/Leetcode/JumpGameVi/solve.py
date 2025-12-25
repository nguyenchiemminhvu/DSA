from typing import List
from collections import deque

class Solution:
    def maxResult(self, nums: List[int], k: int) -> int:
        n = len(nums)

        # memo = {}
        # # F(i) -> max score when jumping from 0 to i
        # def F(i:int) -> int:
        #     if i < 0:
        #         return 0
        #     if i == 0:
        #         return nums[0]
        #     if i in memo:
        #         return memo[i]
        #     score = nums[i]
        #     opt = float('-inf')
        #     for j in range(max(0, i - k), i):
        #         opt = max(opt, F(j))
        #     memo[i] = score + opt
        #     return score + opt
        # return F(n - 1)

        # dp = [0] * n
        # dp[0] = nums[0]
        # for i in range(1, n):
        #     opt = float('inf')
        #     for j in range(max(0, i - k), i):
        #         opt = max(opt, nums[j])
        #     dp[i] = nums[i] + opt
        # return dp[-1]

        dp = [0] * n
        dp[0] = nums[0]
        q = deque([0])
        for i in range(1, n):
            while q and q[0] < i - k:
                q.popleft()
            
            dp[i] = nums[i] + dp[q[0]]

            while q and dp[q[-1]] < dp[i]:
                q.pop()
            q.append(i)
        return dp[-1]