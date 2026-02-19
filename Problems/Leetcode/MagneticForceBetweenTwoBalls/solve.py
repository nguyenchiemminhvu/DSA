from typing import List

class Solution:
    def maxDistance(self, pos: List[int], m: int) -> int:
        pos.sort()
        n = len(pos)

        # check if with distance 'dist'
        # all 'm' ball can be placed in all basket at position 'pos'
        def check_possible(dist: int) -> bool:
            i = 0
            prev_pos = float('-inf')
            count = m
            while i < n:
                diff = pos[i] - prev_pos
                if diff >= dist:
                    count -= 1
                    prev_pos = pos[i]
                i += 1
            return count <= 0

        left = 1
        right = pos[-1] - pos[0]
        res = right
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                res = mid
                left = mid + 1
            else:
                right = mid - 1
        
        return res