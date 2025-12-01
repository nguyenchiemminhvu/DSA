from typing import List

class Solution:
    def maxRunTime(self, n: int, batteries: List[int]) -> int:
        nb = len(batteries)

        # testing if N computer can run simultaneously in T minutes
        def testing(T:int) -> bool:
            s = 0
            for b in batteries:
                s += min(b, T)
            return s >= n * T
        
        left, right = 0, sum(batteries)
        res = left
        while left <= right:
            mid = left + (right - left) // 2
            if testing(mid):
                res = mid
                left = mid + 1
            else:
                right = mid - 1
        return res