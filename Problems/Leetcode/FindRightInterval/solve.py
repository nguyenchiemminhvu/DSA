from typing import List

class Solution:
    def findRightInterval(self, intervals: List[List[int]]) -> List[int]:
        n = len(intervals)
        combined = [[intervals[i][0], intervals[i][1], i] for i in range(n)]
        combined.sort(key=lambda x: (x[0], x[1]))

        res = [-1] * n

        for i, buff in enumerate(combined):
            left, right = 0, n - 1
            idx = n
            while left <= right:
                mid = left + (right - left) // 2
                if combined[mid][0] >= combined[i][1]:
                    idx = mid
                    right = mid - 1
                else:
                    left = mid + 1
            
            if idx < n:
                res[combined[i][2]] = combined[idx][2]

        return res