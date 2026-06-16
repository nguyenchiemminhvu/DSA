from collections import defaultdict
from typing import List

class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        mp = defaultdict(lambda: defaultdict(int)) # mp[(x, y)][slope] -> count of points go through (x, y) with slope

        INF = float('inf')
        def cal_slope(x1, y1, x2, y2):
            if x1 == x2:
                return INF
            return (y2 - y1) / (x2 - x1)

        n = len(points)
        for i in range(n):
            x, y = points[i]

            for j in range(n):
                if j == i:
                    continue
                
                x1, y1 = points[j]
                slope = cal_slope(x, y, x1, y1)

                mp[(x, y)][slope] += 1
        
        res = 1
        for (x, y) in mp.keys():
            for slope in mp[(x, y)]:
                res = max(res, mp[(x, y)][slope] + 1)
        return res