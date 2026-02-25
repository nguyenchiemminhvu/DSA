from typing import List

class Solution:
    def maximumTastiness(self, price: List[int], k: int) -> int:
        price.sort()
        n = len(price)

        def check_possible(max_diff: int) -> bool:
            count = 1
            prev = price[0]
            for val in price:
                if val - prev >= max_diff:
                    count += 1
                    prev = val
            return count >= k

        left = 0
        right = price[-1] - price[0]
        res = 0
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                res = mid
                left = mid + 1
            else:
                right = mid - 1
        return res