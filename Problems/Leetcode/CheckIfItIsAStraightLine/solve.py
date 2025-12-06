from typing import List
import math

class Solution:
    def checkStraightLine(self, c: List[List[int]]) -> bool:
        if len(c) == 2:
            return True
        
        def dot_product(a: List[int], b: List[int]) -> float:
            x1, y1 = a
            x2, y2 = b
            if abs(x2 - x1) == 0:
                return float('inf') # vertical line
            return (y2 - y1) / (x2 - x1)

        c.sort(key=lambda x: (x[0], x[1]))
        orig_dot = dot_product(c[0], c[1])
        for i in range(1, len(c)):
            if dot_product(c[0], c[i]) != orig_dot:
                return False
        return True