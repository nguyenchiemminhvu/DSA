from functools import lru_cache

class Solution:
    def minimumCoins(self, prices: List[int]) -> int:
        n = len(prices)

        # F(i) -> minimum number of coins needed to acquire all the fruits from i to n
        @lru_cache(None)
        def F(i:int) -> int:
            if i >= n:
                return 0
            
            end = min(n, i + (i + 1) + 1)
            return prices[i] + min(F(j) for j in range(i + 1, end + 1))
        
        return F(0)