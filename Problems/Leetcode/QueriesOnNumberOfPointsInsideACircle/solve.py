from typing import List
import math

class Solution:
    def countPoints(self, points: List[List[int]], queries: List[List[int]]) -> List[int]:
        np = len(points)
        nq = len(queries)

        def dist(x1, y1, x2, y2):
            return math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)

        res = []
        for x, y, r in queries:
            count = 0
            for x1, y1 in points:
                if dist(x, y, x1, y1) <= r:
                    count += 1
            res.append(count)
        return res