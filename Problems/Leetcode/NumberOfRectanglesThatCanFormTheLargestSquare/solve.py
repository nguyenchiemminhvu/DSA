from typing import List

class Solution:
    def countGoodRectangles(self, rectangles: List[List[int]]) -> int:
        w = sorted([min(r[0], r[1]) for r in rectangles], reverse=True)
        count = 0
        for val in w:
            if val != w[0]:
                break
            count += 1
        return count