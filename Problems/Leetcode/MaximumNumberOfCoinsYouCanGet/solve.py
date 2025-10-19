from typing import List

class Solution:
    def maxCoins(self, piles: List[int]) -> int:
        piles.sort(reverse=True)
        left = 0
        right = len(piles) - 1
        res = 0
        while left < right:
            res += piles[left + 1]
            left += 2
            right -= 1
        return res