from typing import List

class Solution:
    def maxProfit(self, prices: List[int], strategy: List[int], k: int) -> int:
        n = len(prices)
        half = k // 2

        base_profit = sum(prices[i] * strategy[i] for i in range(n))

        left = 0
        for i in range(half):
            left += -(prices[i] * strategy[i])
        
        right = 0
        for i in range(half, k):
            right += prices[i] * (1 - strategy[i])
        
        best_delta = left + right

        for i in range(1, n - k + 1):
            left -= -(prices[i - 1] * strategy[i - 1])
            left += -(prices[i + half - 1] * strategy[i + half - 1])

            right -= prices[i + half - 1] * (1 - strategy[i + half - 1])
            right += prices[i + k - 1] * (1 - strategy[i + k - 1])

            best_delta = max(best_delta, left + right)
        
        return base_profit + max(0, best_delta)