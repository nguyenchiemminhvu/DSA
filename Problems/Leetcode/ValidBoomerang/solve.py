from typing import List

class Solution:
    def isBoomerang(self, p: List[List[int]]) -> bool:
        if p[0] == p[1] or p[1] == p[2]:
            return False

        x1, y1 = p[0]
        x2, y2 = p[1]
        x3, y3 = p[2]

        if (x2 == x1) and (x3 == x2):
            return False
        if ((x2 == x1) and (x3 != x2)) or ((x2 != x1) and (x3 == x2)):
            return True

        m1 = (y2 - y1) / (x2 - x1)
        m2 = (y3 - y2) / (x3 - x2)
        return m1 != m2