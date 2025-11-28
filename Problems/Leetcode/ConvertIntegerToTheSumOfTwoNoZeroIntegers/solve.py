from typing import List

class Solution:
    def getNoZeroIntegers(self, n: int) -> List[int]:
        def found_0(val: int) -> bool:
            while val:
                if val % 10 == 0:
                    return True
                val //= 10
            return False
        
        l, r = 1, n - 1
        while l <= r:
            if not found_0(l) and not found_0(r):
                return [l, r]
            l += 1
            r -= 1
        return []