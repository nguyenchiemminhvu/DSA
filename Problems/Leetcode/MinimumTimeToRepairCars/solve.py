from typing import List

class Solution:
    def repairCars(self, ranks: List[int], cars: int) -> int:
        n = len(ranks)

        def check_possible(t: int) -> bool:
            count = 0
            for r in ranks:
                count += int(sqrt(t // r))
            return count >= cars

        left, right = 1, max(ranks) * (cars ** 2)
        res = right
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                res = mid
                right = mid - 1
            else:
                left = mid + 1
        return res