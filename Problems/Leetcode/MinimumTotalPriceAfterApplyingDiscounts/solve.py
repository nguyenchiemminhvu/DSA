from typing import List

class Solution:
    def minPrice(self, prices: list[int], discounts: list[int]) -> float:
        prices.sort(reverse=True)
        discounts.sort(reverse=True)
        
        total = 0.0
        n = len(prices)
        m = len(discounts)
        
        for i in range(n):
            if i < m:
                total += prices[i] * (100 - discounts[i]) / 100
            else:
                total += prices[i]
        
        return total