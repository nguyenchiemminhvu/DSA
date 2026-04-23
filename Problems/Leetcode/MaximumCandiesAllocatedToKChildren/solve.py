from typing import List

class Solution:
    def maximumCandies(self, candies: List[int], k: int) -> int:
        n = len(candies)

        def check_possible(val: int) -> bool:
            count = 0
            for candy in candies:
                count += candy // val
            return count >= k

        left = 1
        right = max(candies)
        res = 0
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                res = mid
                left = mid + 1
            else:
                right = mid - 1
        return res