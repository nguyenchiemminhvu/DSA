from typing import List

class Solution:
    def decimalRepresentation(self, n: int) -> List[int]:
        res = []
        base = 0
        while n:
            temp = (n % 10) * (10 ** base)
            if temp:
                res.append(temp)
            n //= 10
            base += 1
        res.reverse()
        return res