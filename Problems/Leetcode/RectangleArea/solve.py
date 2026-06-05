class Solution:
    def computeArea(self, ax1: int, ay1: int, ax2: int, ay2: int, bx1: int, by1: int, bx2: int, by2: int) -> int:
        area1 = (ax2 - ax1) * (ay2 - ay1)
        area2 = (bx2 - bx1) * (by2 - by1)

        # common area section
        left = max(ax1, bx1)
        right = min(ax2, bx2)
        bot = max(ay1, by1)
        top = min(ay2, by2)

        common_area = 0
        if left < right and bot < top:
            common_area = (right - left) * (top - bot)
        
        return area1 + area2 - common_area