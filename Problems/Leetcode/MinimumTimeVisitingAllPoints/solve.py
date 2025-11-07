from typing import List

class Solution:
    def minTimeToVisitAllPoints(self, points: List[List[int]]) -> int:
        def distance(p1: List[int], p2: List[int]) -> int:
            x1, y1 = p1
            x2, y2 = p2
            return max(abs(x2 - x1), abs(y2 - y1))

        res = 0
        n = len(points)
        for i in range(1, n):
            res += distance(points[i - 1], points[i])
        return res