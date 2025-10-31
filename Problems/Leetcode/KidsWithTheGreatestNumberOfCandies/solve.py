from typing import List

class Solution:
    def kidsWithCandies(self, candies: List[int], extraCandies: int) -> List[bool]:
        high = max(candies)
        return [(val + extraCandies) >= high for val in candies]