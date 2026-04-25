from typing import List

class Solution:
    def minSpeedOnTime(self, dist: List[int], hour: float) -> int:
        n = len(dist)

        def check_possible(speed: int) -> bool:
            h = 0
            for i in range(n - 1):
                d = dist[i]
                h += (d + speed - 1) // speed
            h += dist[-1] / speed
            return h <= hour

        left = 1
        right = 1e9
        res = right
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                res = mid
                right = mid - 1
            else:
                left = mid + 1
        return -1 if res == 1e9 else int(res)