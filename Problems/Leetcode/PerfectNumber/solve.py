from typing import List
import math

class Solution:
    def checkPerfectNumber(self, num: int) -> bool:
        def find_divisors(val: int) -> List[int]:
            res = []
            s = int(math.sqrt(val) + 1)
            for i in range(1, s):
                if val % i == 0:
                    res.append(i)
                    if i * i != val and val // i != val:
                        res.append(val // i)
            return res

        if num == 1:
            return False
        div = find_divisors(num)
        return sum(div) == num