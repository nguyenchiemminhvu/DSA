from typing import List

class Solution:
    def isRectangleOverlap(self, rec1: List[int], rec2: List[int]) -> bool:
        rects = [rec1, rec2]
        rects.sort(key=lambda x: (x[0], x[1]))
        rect1, rect2 = rects[0], rects[1]
        x1, y1, x2, y2 = rect1
        xx1, yy1, xx2, yy2 = rect2
        if x2 <= xx1 or y2 <= yy1 or y1 >= yy2:
            return False
        return True