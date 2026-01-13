from typing import List, Tuple

class Solution:
    def separateSquares(self, squares: List[List[int]]) -> float:
        def area(x_bot, y_bot, length, hor: float) -> Tuple[float]:
            x_top, y_top = x_bot, y_bot + length
            if hor >= y_top:
                return (0, length * length)
            if hor <= y_bot:
                return (length * length, 0)
            return ((y_top - hor) * length, (hor - y_bot) * length)
        
        def check(hor: float) -> int:
            area_top, area_bot = 0, 0
            for x, y, l in squares:
                top, bot = area(x, y, l, hor)
                area_top += top
                area_bot += bot
            
            if area_top == area_bot:
                return 0
            if area_top > area_bot:
                return 1
            return -1

        processed = set()
        hor_top = 10**9
        hor_bot = 0
        res = hor_top
        while hor_bot <= hor_top:
            mid = round(hor_bot + (hor_top - hor_bot) / 2, 5)
            if mid in processed:
                break
            else:
                processed.add(mid)
            stat = check(mid)
            if stat <= 0:
                res = round(mid, 5)
                hor_top = mid
            else:
                hor_bot = mid
        return res