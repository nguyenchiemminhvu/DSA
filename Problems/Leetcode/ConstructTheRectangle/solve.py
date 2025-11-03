from typing import List
import math

class Solution:
    def constructRectangle(self, area: int) -> List[int]:
        def get_divisors(val: int) -> List[int]:
            div = []
            sqrt = int(math.sqrt(val)) + 1
            for i in range(1, sqrt):
                if val % i == 0:
                    div.append(i)
                    if i * i != val:
                        div.append(val // i)
            return div
        
        div = sorted(get_divisors(area))

        diff = area
        pair = []
        for w in div:
            l = area // w
            if w > l:
                break
            if l - w < diff:
                pair = [l, w]
        return pair