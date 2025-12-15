from typing import List

class Solution:
    def getDescentPeriods(self, prices: List[int]) -> int:
        n = len(prices)
        dp = [1] * n
        left = 0
        right = 1
        while right < n:
            while right < n and prices[right] + 1 == prices[right - 1]:
                dp[right] += right - left
                right += 1
            left = right
            right += 1

        return sum(dp)