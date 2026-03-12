from typing import List

class Solution:
    def minimumTime(self, time: List[int], totalTrips: int) -> int:
        n = len(time)

        def check_possible(dur: int) -> bool:
            count = 0
            for t in time:
                count += dur // t
            return count >= totalTrips

        left = 1
        right = totalTrips * min(time)
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                right = mid - 1
            else:
                left = mid + 1
        return left