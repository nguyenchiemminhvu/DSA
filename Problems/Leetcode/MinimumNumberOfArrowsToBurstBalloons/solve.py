from typing import List

class Solution:
    def findMinArrowShots(self, points: List[List[int]]) -> int:
        points.sort(key=lambda x: (x[1], x[0]))
        n = len(points)
        removed = 0
        prev = points[0]
        for i in range(1, n):
            if points[i][0] <= prev[1]:
                removed += 1
            else:
                prev = points[i]

        return n - removed