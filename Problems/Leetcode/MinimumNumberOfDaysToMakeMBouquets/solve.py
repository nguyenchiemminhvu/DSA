from typing import List

class Solution:
    def minDays(self, bloom: List[int], m: int, k: int) -> int:
        n = len(bloom)
        if m * k > n:
            return -1
        
        def check_possible(day: int) -> bool:
            # with `day` days, is it possible to have m consecutive flowers length k
            count = 0
            cur = 0
            for b in bloom:
                if day >= b:
                    cur += 1
                else:
                    cur = 0
                if cur >= k:
                    count += 1
                    cur = 0
            return count >= m
        
        left, right = 0, max(bloom)
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                right = mid - 1
            else:
                left = mid + 1
        
        return left