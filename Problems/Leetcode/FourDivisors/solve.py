from typing import List
import math

class Solution:
    def sumFourDivisors(self, nums: List[int]) -> int:
        def get_divs(val:int) -> List[int]:
            divs = []
            n = int(math.sqrt(val)) + 1
            for i in range(1, n):
                if val % i == 0:
                    divs.append(i)
                    if i * i != val:
                        divs.append(val // i)
            return divs
        
        s = 0
        for val in nums:
            divs = get_divs(val)
            if len(divs) == 4:
                s += sum(divs)
        return s